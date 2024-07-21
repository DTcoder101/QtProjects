#ifndef SLIDEPICLISTWIDGET_H
#define SLIDEPICLISTWIDGET_H

#include <QListWidget>
#include <QTreeWidgetItem>
#include <QMap>

class SlidePicListWidget : public QListWidget
{
    Q_OBJECT
public:
    SlidePicListWidget(QWidget *parent = nullptr);

private:
    void AddListItem(const QString& pic_path);
    void ListWidgetPosUpdate(QListWidgetItem *item);

public slots:
    void SlidePicUpdateSlot(QTreeWidgetItem* pic_item);
    void SlidePicUpdateActiveSlot(QTreeWidgetItem* pic_item);

private slots:
    void ItemPressedSlot(QListWidgetItem *item);

signals:
    void PressedItem(QListWidgetItem *item);

private:
    QMap<QString, QListWidgetItem*> slide_list_map;
    QSize list_item_size;
    int current_slide_pic_count;
    QPoint origin_pic_pos;
    int row_max;

};

#endif // SLIDEPICLISTWIDGET_H
