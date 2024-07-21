#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPointF>
QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void mousePressEvent(QMouseEvent *event)override;
    void mouseReleaseEvent(QMouseEvent *event)override;
    void mouseDoubleClickEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void wheelEvent(QWheelEvent *event)override;
protected slots:
    void ok();
private:
    Ui::Widget *ui;
    QPointF mouse_move_offset;
};
#endif // WIDGET_H
