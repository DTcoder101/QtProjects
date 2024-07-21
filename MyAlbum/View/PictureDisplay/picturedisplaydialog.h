#ifndef PICTUREDISPLAYDIALOG_H
#define PICTUREDISPLAYDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include <QPropertyAnimation>

namespace Ui {
class PictureDisplayDialog;
}

class PictureDisplayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PictureDisplayDialog(QWidget *parent = nullptr);
    ~PictureDisplayDialog();

public:
    void FreshPicDisplayArea();

public slots:
    void FreshPicDisplayAreaSlot(QTreeWidgetItem* press_item);
    void CloseProSlot(QTreeWidgetItem* close_pro_root);

protected:
    void resizeEvent(QResizeEvent *event) override;
    bool event(QEvent *event) override;

private slots:
    void on_nextBtn_clicked();
    void on_preBtn_clicked();

private:
    void LoadBrowseBtnPic();
    QString GetCurrentDisplayPicPath();
    std::optional<QPixmap> ScaledPicForShow(const QString& pic_path);
    void UpdatePicArea();

private:
    Ui::PictureDisplayDialog *ui;
    QTreeWidgetItem* current_picture_display_item;
    QPropertyAnimation* pre_btn_animation;
    QPropertyAnimation* next_btn_animation;


signals:
    void SigBrowseNextPic(QTreeWidgetItem* new_item);
    void SigBrowsePrePic(QTreeWidgetItem* new_item);
};

#endif // PICTUREDISPLAYDIALOG_H
