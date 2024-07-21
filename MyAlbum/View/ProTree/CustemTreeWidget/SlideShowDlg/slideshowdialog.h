#ifndef SLIDESHOWDIALOG_H
#define SLIDESHOWDIALOG_H

#include "ConstDef.h"

#include <QDialog>
#include <QTreeWidgetItem>

class QListWidgetItem;

namespace Ui {
class SlideShowDialog;
}

class SlideShowDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SlideShowDialog(QTreeWidgetItem* the_first_pic_item, QWidget *parent = nullptr);
    ~SlideShowDialog();

private slots:
    void on_closeSlideBtn_clicked();
    void on_controlSlideBtn_clicked();
    void on_preSlideBtn_clicked();
    void on_nexSlideBtn_clicked();
    void ControlSlideStop(QListWidgetItem *item);
    void ControlSlideRun(QListWidgetItem *item);

private:
    Ui::SlideShowDialog *ui;
    QTreeWidgetItem* the_first_pic_item;
    SlideShowDlgPlayBtnState play_btn_state;
};

#endif // SLIDESHOWDIALOG_H
