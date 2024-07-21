#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void SetMenu();
    template<typename T>
    void ConnectMenuActionTrigger(QAction* menuAc, T func)
    {
        connect(menuAc, &QAction::triggered, this, func);
    }

private:
    Ui::MainWindow *ui;
    QWidget* pro_tree;
    QWidget* pic_show;

private slots:
    void CreateAcSlot(bool);
    void OpenAcSlot(bool);
    void MusicAcSlot(bool);

signals:
    void OpenProSignal(const QString& dir_name, const QString& dir_path);
};
#endif // MAINWINDOW_H
