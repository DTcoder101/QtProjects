#include "slidepiclistwidget.h"
#include "protreeitem.h"
#include "slidepiclistwidgetitem.h"

#include <QPainter>

SlidePicListWidget::SlidePicListWidget(QWidget *parent):QListWidget(parent)
{
    current_slide_pic_count = 0;
    row_max = 17;

    list_item_size.setWidth(100);
    list_item_size.setHeight(100);

    setViewMode(QListWidget::IconMode);
    setIconSize(list_item_size);
    setSpacing(5);
    setWrapping(false);
    setItemAlignment(Qt::AlignCenter);

    connect(this, &SlidePicListWidget::itemPressed, this, &SlidePicListWidget::ItemPressedSlot);
}

void SlidePicListWidget::SlidePicUpdateSlot(QTreeWidgetItem *pic_item)
{
    if (pic_item == nullptr){
        return;
    }

    protreeitem* current_slide_show_pic_item = dynamic_cast<protreeitem*>(pic_item);
    QString pic_full_path = current_slide_show_pic_item->GetItemFullPath();

    auto slide_list_item =  slide_list_map.find(pic_full_path);
    if (slide_list_item != slide_list_map.end()){
        return;
    }

    AddListItem(pic_full_path);
}

void SlidePicListWidget::SlidePicUpdateActiveSlot(QTreeWidgetItem *pic_item)
{
    if (pic_item == nullptr){
        return;
    }

    auto* the_item = dynamic_cast<protreeitem*>(pic_item);
    QString path = the_item->GetItemFullPath();
    auto iter = slide_list_map.find(path);
    if (iter == slide_list_map.end()){
        return;
    }

    setCurrentItem(iter.value());

    ListWidgetPosUpdate(iter.value());
}

void SlidePicListWidget::AddListItem(const QString &pic_path)
{
    QPixmap cube_backgroud_pic(list_item_size);
    cube_backgroud_pic.fill(QColor(220, 220, 220, 50));

    QPixmap icon_pic(pic_path);
    icon_pic = icon_pic.scaled(list_item_size, Qt::KeepAspectRatio);

    QPainter paint(&cube_backgroud_pic);
    int bg_width = cube_backgroud_pic.width();
    int bg_height = cube_backgroud_pic.height();
    int icon_width = icon_pic.width();
    int icon_height = icon_pic.height();
    int x = (bg_width - icon_width) / 2;
    int y = (bg_height - icon_height) / 2;
    paint.drawPixmap(x, y, icon_pic);

    current_slide_pic_count++;

    SlidePicListWidgetItem* list_item = new SlidePicListWidgetItem(QIcon(cube_backgroud_pic), pic_path,
                                                                   current_slide_pic_count, this);
    list_item->setSizeHint(list_item_size);
    addItem(list_item);

    slide_list_map.insert(pic_path, list_item);

    if (current_slide_pic_count == 1){
        origin_pic_pos = pos();
    }
}

void SlidePicListWidget::ListWidgetPosUpdate(QListWidgetItem *item)
{
    int index = dynamic_cast<SlidePicListWidgetItem*>(item)->getIndex();
    if (index > 17){
        move(origin_pic_pos.x() - (index - row_max) * 105, origin_pic_pos.y());
    }else{
        move(origin_pic_pos);
        row_max = 17;
    }
}

void SlidePicListWidget::ItemPressedSlot(QListWidgetItem *item)
{
    ListWidgetPosUpdate(item);

    emit PressedItem(item);
}
