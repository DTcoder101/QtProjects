#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "childdialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ShowChildWindow();
    void ShowSelf(QString & content);

private:
    Ui::MainWindow *ui;
    ChildDialog* child_dia;
};
#endif // MAINWINDOW_H
