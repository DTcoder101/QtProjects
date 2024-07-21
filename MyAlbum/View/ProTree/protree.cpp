#include "protree.h"
#include "ui_protree.h"

protree::protree(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::protree)
{
    ui->setupUi(this);
    setMinimumWidth(378);
    setMaximumWidth(378);
}

protree::~protree()
{
    delete ui;
}

QTreeWidget *protree::GetCustomWidget()
{
    return dynamic_cast<QTreeWidget*>(ui->treeWidget);
}

void protree::AddProToTree(const QString& name, const QString& path)
{
    ui->treeWidget->AddProToTree(name, path);
}
