#ifndef PROTREEITEM_H
#define PROTREEITEM_H

#include <QTreeWidgetItem>

class protreeitem : public QTreeWidgetItem
{
public:
    explicit protreeitem(QTreeWidget* view, const QString& name,
                         const QString& path, int type = Type);
    explicit protreeitem(QTreeWidgetItem* parent, const QString& name,
                         const QString& path, QTreeWidgetItem* root_nood,
                         int type = Type);

public:
    const QString& getPath() const;
    void setPre_item(QTreeWidgetItem *newPre_item);
    void setNext_item(QTreeWidgetItem *newNext_item);
    QTreeWidgetItem *getRoot_nood() const;
    protreeitem *getPre_item() const;
    protreeitem *getNext_item() const;
    const QString& getName() const;
    QString GetItemFullPath() const;

private:
    QString name;
    QString path;
    QTreeWidgetItem* root_nood;
    QTreeWidgetItem* pre_item;
    QTreeWidgetItem* next_item;
};

#endif // PROTREEITEM_H
