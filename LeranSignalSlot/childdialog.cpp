#include "childdialog.h"
#include "ui_childdialog.h"

ChildDialog::ChildDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChildDialog)
{
    ui->setupUi(this);

    connect(ui->displayMainWindow, &QPushButton::clicked, this, &ChildDialog::ShowMainWindow);
}

ChildDialog::~ChildDialog()
{
    delete ui;
}

void ChildDialog::ShowMainWindow()
{
    QString str("heihei ! fucker!!");
    this->hide();
    emit ShowMainSingnal(str);
}
