#include "childdialog.h"
#include "ui_childdialog.h"

ChildDialog::ChildDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChildDialog)
{
    ui->setupUi(this);
}

ChildDialog::~ChildDialog()
{
    delete ui;
}
