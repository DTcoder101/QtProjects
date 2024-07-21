#include "mydelegate.h"
#include <QSpinBox>


Mydelegate::Mydelegate(QObject *parent)
{

}

QWidget *Mydelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSpinBox* box = new QSpinBox(parent);
    box->setMinimum(0);
    box->setMaximum(100);
    return box;
}

void Mydelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.data(Qt::EditRole).toInt();
    QSpinBox* the_box = dynamic_cast<QSpinBox*>(editor);
    the_box->setValue(value);
}

void Mydelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox* the_box = dynamic_cast<QSpinBox*>(editor);
    the_box->interpretText();
    int val = the_box->value();
    model->setData(index, val, Qt::EditRole);
}

void Mydelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
