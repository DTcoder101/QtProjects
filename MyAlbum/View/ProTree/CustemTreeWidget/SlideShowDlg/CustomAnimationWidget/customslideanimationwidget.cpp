#include "customslideanimationwidget.h"
#include "protreeitem.h"
#include "ConstDef.h"
#include "slidepiclistwidgetitem.h"

#include <QTimer>
#include <QPainter>
#include <QListWidgetItem>


CustomSlideAnimationWidget::CustomSlideAnimationWidget(QWidget *parent)
    : QWidget{parent}
{
    first_pic_item = nullptr;
    current_pic_item = nullptr;
    timer = new QTimer(this);
    factor = 0.0f;
    run_flag = false;
    finish_flag = false;
    list_item_pressed_flag = false;

    connect(timer, &QTimer::timeout, this, &CustomSlideAnimationWidget::TimeOut);
}

void CustomSlideAnimationWidget::SetCurrentSlideShowPicItem(QTreeWidgetItem *pic_item)
{
    if (pic_item == nullptr){
        return;
    }

    protreeitem* the_pic_item = dynamic_cast<protreeitem*>(pic_item);
    do{
        current_pic_item = the_pic_item;
        the_pic_item = the_pic_item->getNext_item();
    }while(current_pic_item->type() != TreeItemType::treeItemPic);

    the_pic_item = dynamic_cast<protreeitem*>(current_pic_item);

    QString pic_full_path = the_pic_item->GetItemFullPath();
    present_pic_buffer.load(pic_full_path);

    if (slide_show_item_map.find(pic_full_path) == slide_show_item_map.end()){
        slide_show_item_map.insert(pic_full_path, the_pic_item);
        /*emit the signal to list widget for update,
            when the picture first display in slide show area.*/
        emit UpdateListWidgetSig(the_pic_item);
    }

    emit UpdateListWidgetActiveSig(the_pic_item);

    protreeitem* the_next_pic_item = the_pic_item->getNext_item();
    if (the_next_pic_item == nullptr){
        return;
    }
    pic_full_path = the_next_pic_item->GetItemFullPath();
    future_pic_buffer.load(pic_full_path);
    if (slide_show_item_map.find(pic_full_path) == slide_show_item_map.end()){
        slide_show_item_map.insert(pic_full_path, the_next_pic_item);
        /*emit the signal to list widget for update,
            when the picture first display in slide show area.*/
        emit UpdateListWidgetSig(the_next_pic_item);
    }
}

void CustomSlideAnimationWidget::SetFirstSlideShowPicItem(QTreeWidgetItem *pic_item)
{
    if (pic_item == nullptr){
        return;
    }

    protreeitem* the_pic_item = dynamic_cast<protreeitem*>(pic_item);
    do{
        first_pic_item = the_pic_item;
        the_pic_item = the_pic_item->getNext_item();
    }while(first_pic_item->type() != TreeItemType::treeItemPic);
}

void CustomSlideAnimationWidget::Start()
{
    factor = 0.0f;
    run_flag = true;
    timer->start(10);
}

void CustomSlideAnimationWidget::ContinueStart()
{
    if (run_flag){
        return;
    }

    factor = 0.0f;
    run_flag = true;

    if (finish_flag){
        finish_flag = false;
        current_pic_item = first_pic_item;
        timer->start(10);
    }else{
        timer->start();
    }
}

void CustomSlideAnimationWidget::Stop()
{
    timer->stop();
    run_flag = false;
    factor = 0.0f;
}

void CustomSlideAnimationWidget::paintEvent(QPaintEvent *event)
{
    if (present_pic_buffer.isNull()){
        return;
    }

    QPainter paint(this);
    paint.setRenderHint(QPainter::Antialiasing);

    QRect rect = this->geometry();
    int height = rect.height();
    int width = rect.width();
    present_pic_buffer = present_pic_buffer.scaled(width, height, Qt::KeepAspectRatio);

    QPixmap alphMap(present_pic_buffer.size());
    alphMap.fill(Qt::transparent);

    //the painter p1 draw the picture to alphMap.
    QPainter p1(&alphMap);
    p1.setCompositionMode(QPainter::CompositionMode_Source);
    p1.drawPixmap(0, 0, present_pic_buffer);
    p1.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    int alphVal = 255 * (1 - factor);
    p1.fillRect(alphMap.rect(), QColor(0, 0, 0, alphVal));
    p1.end();

    //the painter paint draw the alphMap,
        //because the alphMap was drawed the picture by the p1.
        //show alphMap, the picture will show.
    int x = (width - alphMap.width()) / 2;
    int y = (height - alphMap.height()) / 2;
        paint.drawPixmap(x, y, alphMap);

    if (future_pic_buffer.isNull()){
        return;
    }

    future_pic_buffer = future_pic_buffer.scaled(width, height, Qt::KeepAspectRatio);

    QPixmap future_alph_map(future_pic_buffer.size());
    future_alph_map.fill(Qt::transparent);

    QPainter p2(&future_alph_map);
    p2.setCompositionMode(QPainter::CompositionMode_Source);
    p2.drawPixmap(0, 0, future_pic_buffer);
    p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    int future_alphVal = 255 * factor;
    p2.fillRect(future_alph_map.rect(), QColor(0, 0, 0, future_alphVal));
    p2.end();

    x = (width - future_alph_map.width()) / 2;
    y = (height - future_alph_map.height()) / 2;
    paint.drawPixmap(x, y, future_alph_map);
}

void CustomSlideAnimationWidget::SlideShowUpdate(QListWidgetItem *item)
{
    list_item_pressed_flag = true;
    auto * the_item = dynamic_cast<SlidePicListWidgetItem*>(item);

    QString path = the_item->getPath();

    auto iter = slide_show_item_map.find(path);
    if (iter == slide_show_item_map.end()){
        return;
    }

    SetCurrentSlideShowPicItem(iter.value());
    ContinueStart();
}

void CustomSlideAnimationWidget::TimeOut()
{
    if (current_pic_item == nullptr){
        Stop();
        update();
        return;
    }

    factor += 0.01f;
    if (factor >= 1){
        factor = 0.0f;

        if (list_item_pressed_flag){
            Stop();
            update();
            list_item_pressed_flag = false;
            return;
        }

        protreeitem* the_pic_item = dynamic_cast<protreeitem*>(current_pic_item);
        protreeitem* the_next_pic_item = the_pic_item->getNext_item();
        if (the_next_pic_item == nullptr){
            Stop();
            update();
            finish_flag = true;
            return;
        }

        SetCurrentSlideShowPicItem(the_next_pic_item);
        update();
        return;
    }

    update();
}

