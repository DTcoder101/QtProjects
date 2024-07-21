#ifndef BROWSEPICBTN_H
#define BROWSEPICBTN_H

#include <QPushButton>
#include <QEvent>

class BrowsePicBtn : public QPushButton
{
public:
    explicit BrowsePicBtn(QWidget *parent = nullptr);
    ~BrowsePicBtn();

public:
    void setNormal_pic_path(const QString &newNormal_pic_path);
    void setHover_pic_path(const QString &newHover_pic_path);
    void setPressed_pic_path(const QString &newPressed_pic_path);

protected:
    bool event(QEvent *e) override;

private:
    void SetBtnPic(const QString& pic_path);

private:
    QString normal_pic_path;
    QString hover_pic_path;
    QString pressed_pic_path;
};

#endif // BROWSEPICBTN_H
