#include "browsepicbtn.h"

#include <QIcon>
#include <QPixmap>


BrowsePicBtn::BrowsePicBtn(QWidget *parent):QPushButton(parent)
{
    this->normal_pic_path = "";
    this->hover_pic_path = "";
    this->pressed_pic_path = "";
}

BrowsePicBtn::~BrowsePicBtn()
{

}

void BrowsePicBtn::setNormal_pic_path(const QString &newNormal_pic_path)
{
    normal_pic_path = newNormal_pic_path;
}

void BrowsePicBtn::setHover_pic_path(const QString &newHover_pic_path)
{
    hover_pic_path = newHover_pic_path;
}

void BrowsePicBtn::setPressed_pic_path(const QString &newPressed_pic_path)
{
    pressed_pic_path = newPressed_pic_path;
}

bool BrowsePicBtn::event(QEvent *e)
{
    QString current_btn_pic_path = "";
    switch (e->type()) {
    case QEvent::Enter:
        current_btn_pic_path = hover_pic_path;
        break;
    case QEvent::MouseButtonPress:
        current_btn_pic_path = pressed_pic_path;
        break;
    case QEvent::MouseButtonRelease:
        current_btn_pic_path = hover_pic_path;
        break;
    case QEvent::Leave:
        current_btn_pic_path = normal_pic_path;
        break;
    default:
        current_btn_pic_path = normal_pic_path;
        break;
    }

    SetBtnPic(current_btn_pic_path);

    return QPushButton::event(e);
}

void BrowsePicBtn::SetBtnPic(const QString &pic_path)
{
    if (pic_path == ""){
        return;
    }

    QPixmap current_btn_pic(pic_path);
    resize(current_btn_pic.size());
    setIcon(current_btn_pic);
    setIconSize(current_btn_pic.size());
}
