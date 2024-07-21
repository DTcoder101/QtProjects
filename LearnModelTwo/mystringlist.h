#ifndef MYSTRINGLIST_H
#define MYSTRINGLIST_H

#include <QAbstractListModel>
#include <QStringList>

class MyStringList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyStringList(const QStringList& strs, QObject *parent = nullptr);

public:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QStringList str_list;
};

#endif // MYSTRINGLIST_H
