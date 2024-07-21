#ifndef SLIDEPICLISTWIDGETITEM_H
#define SLIDEPICLISTWIDGETITEM_H

#include <QListWidgetItem>

class SlidePicListWidgetItem : public QListWidgetItem
{
public:
    SlidePicListWidgetItem(const QIcon &icon, const QString &text, int index,
                           QListWidget *listview = nullptr, int type = Type);


    QString getPath() const;

    int getIndex() const;

private:
    QString path;
    int index;
};

#endif // SLIDEPICLISTWIDGETITEM_H
