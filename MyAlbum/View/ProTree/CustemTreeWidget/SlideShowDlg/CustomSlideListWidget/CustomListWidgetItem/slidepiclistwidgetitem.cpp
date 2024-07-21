#include "slidepiclistwidgetitem.h"

SlidePicListWidgetItem::SlidePicListWidgetItem(const QIcon &icon, const QString &text,
                                               int index, QListWidget *listview, int type):
    QListWidgetItem(icon, "", listview, type)

{
    path = text;
    this->index = index;
}

QString SlidePicListWidgetItem::getPath() const
{
    return path;
}

int SlidePicListWidgetItem::getIndex() const
{
    return index;
}
