#include "wizard.h"
#include "ui_wizard.h"

#include <QDialog>
#include <QDir>

Wizard::Wizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::Wizard)
{
    ui->setupUi(this);
}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::done(int result)
{
    if (result == QDialog::Rejected){
        return QWizard::done(result);
    }

    QString proName, proPath;
    ui->wizardPage1->GetProSetting(proName, proPath);

    QDir dir(proPath);
    QString file_all_path = dir.absoluteFilePath(proName);
    QDir pro_dir(file_all_path);
    if (!pro_dir.exists()){
        bool ret = pro_dir.mkpath(file_all_path);
        if (!ret){
            return;
        }
    }

    emit ProPathGet(proName, proPath);

    QWizard::done(result);
}
