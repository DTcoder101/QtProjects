#ifndef MYDELEGATE_H
#define MYDELEGATE_H
#include <QItemDelegate>
class Mydelegate : public QItemDelegate
{
    Q_OBJECT
public:
    Mydelegate(QObject *parent = nullptr);
    ~Mydelegate() = default;
public:
    QWidget *createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;
};

#endif // MYDELEGATE_H
