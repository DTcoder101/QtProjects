#include "mystringlist.h"


MyStringList::MyStringList(const QStringList &strs, QObject *parent):QAbstractListModel(parent)
{
    str_list = strs;
}

QVariant MyStringList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (index.row() >= str_list.size())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
    {
        return QVariant();
    }

    return str_list.at(index.row());
}

bool MyStringList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
    {
        return false;
    }

    if (role != Qt::EditRole)
    {
        return false;
    }

    str_list.replace(index.row(), value.toString());
    emit dataChanged(index, index);
    return true;
}

QVariant MyStringList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        return QString("Column %1").arg(section);
    }
    else
    {
        return QString("Row %1").arg(section);
    }
}

int MyStringList::rowCount(const QModelIndex &parent) const
{
    return str_list.size();
}

bool MyStringList::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, (row + count) - 1);

    for (uint32_t i = 0; i < count; i++)
    {
        str_list.insert(row + i, QString::number(i));
    }

    endInsertRows();

    return true;
}

bool MyStringList::removeRows(int row, int count, const QModelIndex &parent)
{
    return false;
}

Qt::ItemFlags MyStringList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsEnabled;
    }

    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}
