#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>

namespace Ui {
class ChildDialog;
}

class ChildDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChildDialog(QWidget *parent = nullptr);
    ~ChildDialog();

signals:
    void ShowMainSingnal(QString & content);

private slots:
    void ShowMainWindow();
private:
    Ui::ChildDialog *ui;
};

#endif // CHILDDIALOG_H
