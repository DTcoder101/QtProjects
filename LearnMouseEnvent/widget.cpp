#include "widget.h"
#include "ui_widget.h"
#include <QCursor>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        QCursor cur;
        cur.setShape(Qt::ClosedHandCursor);
        QApplication::setOverrideCursor(cur);

        mouse_move_offset = event->globalPosition() - pos();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QApplication::restoreOverrideCursor();
}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (this->windowState() == Qt::WindowFullScreen)
            this->setWindowState(Qt::WindowNoState);
        else
            this->setWindowState(Qt::WindowFullScreen);
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF window_new_pos = event->globalPosition() - mouse_move_offset;
        this->move(window_new_pos.x(), window_new_pos.y());
    }
}

void Widget::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
    {
        ui->textEdit->zoomIn();
    }
    else
    {
        ui->textEdit->zoomOut();
    }
}
