#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    child_dia = new ChildDialog(this);
    connect(ui->childWindowDIsplay, &QPushButton::clicked, this, &MainWindow::ShowChildWindow);
    connect(child_dia, &ChildDialog::ShowMainSingnal, this, &MainWindow::ShowSelf);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete child_dia;
}

void MainWindow::ShowChildWindow()
{
    this->hide();
    child_dia->show();
}

void MainWindow::ShowSelf(QString & content)
{
    ui->label->setText(content);
    this->show();
}
