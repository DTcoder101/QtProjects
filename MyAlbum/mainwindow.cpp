#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wizard.h"
#include "protree.h"
#include "protreewidget.h"
#include "picturedisplaydialog.h"

#include <QFileDialog>
#include <QStringList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SetMenu();

    pro_tree = new protree(this);
    pic_show = new PictureDisplayDialog(this);

    ui->proLayout->addWidget(pro_tree);
    ui->workLayout->addWidget(pic_show);

    QTreeWidget* pro_tree_widget = dynamic_cast<protree*>(pro_tree)->GetCustomWidget();

    connect(this, &MainWindow::OpenProSignal,
            dynamic_cast<protreewidget*>(pro_tree_widget), &protreewidget::OpenProToTree);

    connect(dynamic_cast<protreewidget*>(pro_tree_widget), &protreewidget::SigFreshPicDisplayArea,
            dynamic_cast<PictureDisplayDialog*>(pic_show), &PictureDisplayDialog::FreshPicDisplayAreaSlot);
    connect(dynamic_cast<protreewidget*>(pro_tree_widget), &protreewidget::SigClosePro,
            dynamic_cast<PictureDisplayDialog*>(pic_show), &PictureDisplayDialog::CloseProSlot);

    connect(dynamic_cast<PictureDisplayDialog*>(pic_show), &PictureDisplayDialog::SigBrowseNextPic,
            dynamic_cast<protreewidget*>(pro_tree_widget), &protreewidget::FreshNewSelectItem);
    connect(dynamic_cast<PictureDisplayDialog*>(pic_show), &PictureDisplayDialog::SigBrowsePrePic,
            dynamic_cast<protreewidget*>(pro_tree_widget), &protreewidget::FreshNewSelectItem);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    // dynamic_cast<PictureDisplayDialog*>(pic_show)->FreshPicDisplayArea();

    QMainWindow::resizeEvent(event);
}

void MainWindow::SetMenu()
{
    QMenu* menuBarPro = menuBar()->addMenu(tr("项目(&F)"));
    QAction* fileMenuAcCreate = new QAction(tr("创建项目"), menuBarPro);
    fileMenuAcCreate->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_N));
    menuBarPro->addAction(fileMenuAcCreate);

    QAction* fileMenuAcOpen = new QAction(tr("打开项目"), menuBarPro);
    fileMenuAcOpen->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    menuBarPro->addAction(fileMenuAcOpen);

    QMenu* menuBarSet = menuBar()->addMenu(tr("设置(&S)"));
    QAction* fileMenuAcMusic = new QAction(tr("背景音乐"), menuBarSet);
    fileMenuAcMusic->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_M));
    menuBarSet->addAction(fileMenuAcMusic);

    ConnectMenuActionTrigger(fileMenuAcCreate, &MainWindow::CreateAcSlot);
    ConnectMenuActionTrigger(fileMenuAcOpen, &MainWindow::OpenAcSlot);
    ConnectMenuActionTrigger(fileMenuAcMusic, &MainWindow::MusicAcSlot);
}

void MainWindow::CreateAcSlot(bool)
{
    Wizard wizard(this);
    wizard.setWindowTitle(tr("创建项目"));

    QWizardPage* pagePtr = wizard.page(0);
    pagePtr->setTitle(tr("设置项目"));

    connect(&wizard, &Wizard::ProPathGet,
            dynamic_cast<protree*>(pro_tree), &protree::AddProToTree);

    wizard.exec();
}

void MainWindow::OpenAcSlot(bool)
{
    QFileDialog open_pro_dialog;
    open_pro_dialog.setFileMode(QFileDialog::Directory);
    open_pro_dialog.setWindowTitle(tr("选择要打开的文件夹"));
    open_pro_dialog.setDirectory(QDir::currentPath());

    QStringList file_names;
    if (open_pro_dialog.exec()){
        file_names = open_pro_dialog.selectedFiles();
    }
    if (file_names.length() <= 0){
        return;
    }

    //send the open project signal to tree widget.
    QDir target_dir(file_names.at(0));
    QString dir_name = target_dir.dirName();
    if (!target_dir.cdUp()){
        return;
    }
    emit OpenProSignal(dir_name, target_dir.path());
}

void MainWindow::MusicAcSlot(bool)
{

}


