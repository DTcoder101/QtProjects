#include "prosetpage.h"
#include "ui_prosetpage.h"

#include <QDir>
#include <QFileDialog>

ProSetPage::ProSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProSetPage)
{
    ui->setupUi(this);

    // registerField("proName", ui->lineEdit);
    // registerField("proPath*", ui->lineEdit_2);

    ConnectSignal();
    SetPathLineEdit();
}

ProSetPage::~ProSetPage()
{
    delete ui;
}

void ProSetPage::GetProSetting(QString &proName, QString &proPath)
{
    proName = ui->lineEdit->text();
    proPath = ui->lineEdit_2->text();
}

bool ProSetPage::isComplete() const
{
    if (ui->lineEdit->text() == "" || ui->lineEdit_2->text() == ""){
        return false;
    }

    QDir dir(ui->lineEdit_2->text());
    if (!dir.exists()){
        ui->tips->setText("The project path is not available!");
        return false;
    }

    QString abs_path = dir.absoluteFilePath(ui->lineEdit->text());
    QDir pro_dir(abs_path);
    if (pro_dir.exists()){
        ui->tips->setText("The project has existed, use other name!");
        return false;
    }

    ui->tips->setText("");

    return QWizardPage::isComplete();
}

void ProSetPage::ConnectSignal()
{
    ConnectLineEditCompleteChange(ui->lineEdit, &ProSetPage::completeChanged);
    ConnectLineEditCompleteChange(ui->lineEdit_2, &ProSetPage::completeChanged);
}

void ProSetPage::SetPathLineEdit()
{
    QString curPath = QDir::currentPath();
    ui->lineEdit_2->setText(curPath);
    ui->lineEdit_2->setCursorPosition(curPath.size());
    ui->lineEdit_2->setClearButtonEnabled(true);

    ui->lineEdit->setClearButtonEnabled(true);
}

void ProSetPage::on_pushButton_clicked()
{
    QFileDialog file_dlg;
    QString cur_path = QDir::currentPath();
    file_dlg.setFileMode(QFileDialog::Directory);
    file_dlg.setWindowTitle("选择要打开的目录");
    file_dlg.setDirectory(cur_path);
    file_dlg.setViewMode(QFileDialog::Detail);

    QStringList all_dir_path;
    if (file_dlg.exec()){
        all_dir_path = file_dlg.selectedFiles();
    }

    if (all_dir_path.length() <= 0){
        return;
    }

    ui->lineEdit_2->setText(all_dir_path.at(0));
}

