#include "slideshowdialog.h"
#include "ui_slideshowdialog.h"

#include <QListWidgetItem>

SlideShowDialog::SlideShowDialog(QTreeWidgetItem* the_first_pic_item, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SlideShowDialog)
{
    ui->setupUi(this);
    this->the_first_pic_item = the_first_pic_item;
    play_btn_state = SlideShowDlgPlayBtnState::play;
    ui->controlSlideBtn->setText(tr("暂停"));

    connect(ui->slideAnimationWidget, &CustomSlideAnimationWidget::UpdateListWidgetSig,
            ui->picSlideListWidget, &SlidePicListWidget::SlidePicUpdateSlot);

    connect(ui->slideAnimationWidget, &CustomSlideAnimationWidget::UpdateListWidgetActiveSig,
            ui->picSlideListWidget, &SlidePicListWidget::SlidePicUpdateActiveSlot);

    connect(ui->picSlideListWidget, &SlidePicListWidget::itemPressed,
            this, &SlideShowDialog::ControlSlideStop);
    connect(ui->picSlideListWidget, &SlidePicListWidget::PressedItem,
            ui->slideAnimationWidget, &CustomSlideAnimationWidget::SlideShowUpdate);

    ui->slideAnimationWidget->SetFirstSlideShowPicItem(the_first_pic_item);
    ui->slideAnimationWidget->SetCurrentSlideShowPicItem(the_first_pic_item);
    ui->slideAnimationWidget->Start();
}

SlideShowDialog::~SlideShowDialog()
{
    delete ui;
}

void SlideShowDialog::on_closeSlideBtn_clicked()
{
    ui->slideAnimationWidget->Stop();
    close();
    // destroy();
}


void SlideShowDialog::on_controlSlideBtn_clicked()
{
    if (play_btn_state == SlideShowDlgPlayBtnState::stop){
        ControlSlideRun(nullptr);
    }else{
        ControlSlideStop(nullptr);
    }
}


void SlideShowDialog::on_preSlideBtn_clicked()
{

}


void SlideShowDialog::on_nexSlideBtn_clicked()
{

}

void SlideShowDialog::ControlSlideStop(QListWidgetItem *item)
{
    if (play_btn_state == SlideShowDlgPlayBtnState::stop){
        return;
    }

    play_btn_state = SlideShowDlgPlayBtnState::stop;
    ui->slideAnimationWidget->Stop();
    ui->controlSlideBtn->setText(tr("暂停"));
}

void SlideShowDialog::ControlSlideRun(QListWidgetItem *item)
{
    if (play_btn_state == SlideShowDlgPlayBtnState::play){
        return;
    }

    play_btn_state = SlideShowDlgPlayBtnState::play;
    ui->slideAnimationWidget->ContinueStart();
    ui->controlSlideBtn->setText(tr("播放"));
}

