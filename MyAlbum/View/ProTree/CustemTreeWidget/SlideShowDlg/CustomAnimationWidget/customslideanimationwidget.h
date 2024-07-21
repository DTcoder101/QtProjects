#ifndef CUSTOMSLIDEANIMATIONWIDGET_H
#define CUSTOMSLIDEANIMATIONWIDGET_H

#include <QWidget>
#include <QTreeWidgetItem>
#include <QPixmap>

class QListWidgetItem;

class CustomSlideAnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomSlideAnimationWidget(QWidget *parent = nullptr);
    ~CustomSlideAnimationWidget() = default;

public:
    void SetCurrentSlideShowPicItem(QTreeWidgetItem* pic_item);
    void SetFirstSlideShowPicItem(QTreeWidgetItem* pic_item);
    void Start();
    void ContinueStart();
    void Stop();

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void UpdateListWidgetSig(QTreeWidgetItem* pic_item);
    void UpdateListWidgetActiveSig(QTreeWidgetItem* pic_item);

public slots:
    void SlideShowUpdate(QListWidgetItem* item);

private slots:
    void TimeOut();

private:
    QTreeWidgetItem* current_pic_item;
    QTreeWidgetItem* first_pic_item;
    //double buffer for slide all project picture.
    QPixmap present_pic_buffer;
    QPixmap future_pic_buffer;

    QMap<QString, QTreeWidgetItem*> slide_show_item_map;
    QTimer* timer;
    float factor;
    bool run_flag;
    bool finish_flag;
    bool list_item_pressed_flag;
};

#endif // CUSTOMSLIDEANIMATIONWIDGET_H
