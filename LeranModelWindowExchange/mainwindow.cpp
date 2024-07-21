#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    childWindow = new ChildDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_enterChild_clicked()
{
    this->close();
    if (childWindow->exec() == ChildDialog::Accepted)
    {
        this->show();
    }

    childWindow->close();
}

