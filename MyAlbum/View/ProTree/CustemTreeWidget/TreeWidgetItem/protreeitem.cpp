#include "protreeitem.h"

#include <QDir>

protreeitem::protreeitem(QTreeWidget* view, const QString& name,
                         const QString& path, int type):QTreeWidgetItem(view, type)
{
    this->root_nood = this;
    this->pre_item = nullptr;
    this->next_item = nullptr;
    this->name = name;
    this->path = path;
}
protreeitem::protreeitem(QTreeWidgetItem *parent, const QString &name,
                         const QString &path,QTreeWidgetItem *root_nood,
                         int type):QTreeWidgetItem(parent, type)
{
    this->pre_item = nullptr;
    this->next_item = nullptr;
    this->name = name;
    this->path = path;
    this->root_nood = root_nood;
}

const QString &protreeitem::getPath() const
{
    return path;
}

void protreeitem::setPre_item(QTreeWidgetItem *newPre_item)
{
    pre_item = newPre_item;
}

void protreeitem::setNext_item(QTreeWidgetItem *newNext_item)
{
    next_item = newNext_item;
}

QTreeWidgetItem *protreeitem::getRoot_nood() const
{
    return root_nood;
}

protreeitem *protreeitem::getPre_item() const
{
    return dynamic_cast<protreeitem*>(pre_item);
}

protreeitem *protreeitem::getNext_item() const
{
    return dynamic_cast<protreeitem*>(next_item);
}

const QString &protreeitem::getName() const
{
    return name;
}

QString protreeitem::GetItemFullPath() const
{
    QDir item_path(path);
    return item_path.absoluteFilePath(name);
}
