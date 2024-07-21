#include "picturedisplaydialog.h"
#include "ui_picturedisplaydialog.h"
#include "ConstDef.h"
#include "protreeitem.h"

#include <QDir>
#include <QPixmap>
#include <QPixmapCache>
#include <QResizeEvent>
#include <QGraphicsOpacityEffect>


PictureDisplayDialog::PictureDisplayDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PictureDisplayDialog)
{
    current_picture_display_item = nullptr;
    ui->setupUi(this);

    LoadBrowseBtnPic();

    QGraphicsOpacityEffect* pre_opacity = new QGraphicsOpacityEffect(this);
    pre_opacity->setOpacity(0);
    ui->preBtn->setGraphicsEffect(pre_opacity);

    QGraphicsOpacityEffect* next_opacity = new QGraphicsOpacityEffect(this);
    next_opacity->setOpacity(0);
    ui->nextBtn->setGraphicsEffect(next_opacity);

    pre_btn_animation = new QPropertyAnimation(pre_opacity, "opacity", this);
    pre_btn_animation->setEasingCurve(QEasingCurve::Linear);
    pre_btn_animation->setDuration(500);

    next_btn_animation = new QPropertyAnimation(next_opacity, "opacity", this);
    next_btn_animation->setEasingCurve(QEasingCurve::Linear);
    next_btn_animation->setDuration(500);
}

PictureDisplayDialog::~PictureDisplayDialog()
{
    delete ui;
}

void PictureDisplayDialog::FreshPicDisplayArea()
{
    UpdatePicArea();
}

void PictureDisplayDialog::FreshPicDisplayAreaSlot(QTreeWidgetItem* press_item)
{
    if (press_item == nullptr){
        return;
    }

    if (press_item->type() != TreeItemType::treeItemPic){
        return;
    }

    current_picture_display_item = press_item;

    UpdatePicArea();
}

void PictureDisplayDialog::CloseProSlot(QTreeWidgetItem *close_pro_root)
{
    if (current_picture_display_item == nullptr){
        return;
    }

    if (close_pro_root == dynamic_cast<protreeitem*>(current_picture_display_item)->getRoot_nood()){
        ui->displayPicArea->clear();
    }
}

void PictureDisplayDialog::resizeEvent(QResizeEvent *event)
{
    UpdatePicArea();

    QDialog::resizeEvent(event);
}

bool PictureDisplayDialog::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::Enter:
        pre_btn_animation->setEndValue(1);
        pre_btn_animation->setStartValue(0);
        pre_btn_animation->start();

        next_btn_animation->setEndValue(1);
        next_btn_animation->setStartValue(0);
        next_btn_animation->start();
        break;
    case QEvent::Leave:
        pre_btn_animation->setEndValue(0);
        pre_btn_animation->setStartValue(1);
        pre_btn_animation->start();

        next_btn_animation->setEndValue(0);
        next_btn_animation->setStartValue(1);
        next_btn_animation->start();
        break;
    default:
        break;
    }

    return QDialog::event(event);
}

void PictureDisplayDialog::LoadBrowseBtnPic()
{
    ui->preBtn->setHover_pic_path(":/btn_pic/pre_hover.png");
    ui->preBtn->setNormal_pic_path(":/btn_pic/pre_normal.png");
    ui->preBtn->setPressed_pic_path(":/btn_pic/pre_pressed.png");

    ui->nextBtn->setHover_pic_path(":/btn_pic/next_hover.png");
    ui->nextBtn->setNormal_pic_path(":/btn_pic/next_normal.png");
    ui->nextBtn->setPressed_pic_path(":/btn_pic/next_pressed.png");
}

QString PictureDisplayDialog::GetCurrentDisplayPicPath()
{
    if (current_picture_display_item == nullptr){
        return "";
    }

    QString pic_path_str = dynamic_cast<protreeitem*>(current_picture_display_item)->getPath();
    QString pic_name_str = dynamic_cast<protreeitem*>(current_picture_display_item)->getName();
    QDir pic_path(pic_path_str);

    return pic_path.absoluteFilePath(pic_name_str);
}

std::optional<QPixmap> PictureDisplayDialog::ScaledPicForShow(const QString &pic_path)
{
    if (pic_path == ""){
        return std::nullopt;
    }

    QPixmap pic(pic_path);
    int org_width = pic.width();
    int org_height = pic.height();
    int fix_width, fix_height, offset = 0;
    QSize current_dialog_size = size();
    int new_dlg_w = current_dialog_size.width() - ui->nextBtn->width() * 2 - 100;
    int new_dig_h = current_dialog_size.height() - 90;

    ui->displayPicArea->setGeometry(0, 0, new_dlg_w , new_dig_h);

    if (org_width / new_dlg_w >= org_height / new_dig_h){
        offset = org_width / new_dlg_w;
    }else {
        offset = org_height / new_dig_h;
    }

    fix_width = org_width / offset;
    fix_height = org_height / offset;

    std::optional<QPixmap> new_pic = pic.scaled(fix_width, fix_height, Qt::KeepAspectRatio);

    return new_pic;
}

void PictureDisplayDialog::UpdatePicArea()
{
    QString pic_path = GetCurrentDisplayPicPath();
    std::optional<QPixmap> new_pic = ScaledPicForShow(pic_path);
    if (new_pic == std::nullopt){
        return;
    }
    ui->displayPicArea->setPixmap(new_pic.value());

    // int&& width = ui->gridLayout->geometry().width();
    // int&& height = ui->gridLayout->geometry().height();

    // QPixmap pm(pic_path);
    // pm = pm.scaled(width - 30, height - 40, Qt::KeepAspectRatio);
    // ui->displayPicArea->setPixmap(pm);
}

void PictureDisplayDialog::on_nextBtn_clicked()
{
    if (current_picture_display_item == nullptr){
        return;
    }

    QTreeWidgetItem* next_pic_item = dynamic_cast<protreeitem*>(current_picture_display_item)->getNext_item();
    if (next_pic_item == nullptr){
        return;
    }

    emit SigBrowseNextPic(next_pic_item);
    FreshPicDisplayAreaSlot(next_pic_item);
}


void PictureDisplayDialog::on_preBtn_clicked()
{
    if (current_picture_display_item == nullptr){
        return;
    }

    QTreeWidgetItem* pre_pic_item = dynamic_cast<protreeitem*>(current_picture_display_item)->getPre_item();
    if (pre_pic_item == nullptr){
        return;
    }

    emit SigBrowsePrePic(pre_pic_item);
    FreshPicDisplayAreaSlot(pre_pic_item);
}

