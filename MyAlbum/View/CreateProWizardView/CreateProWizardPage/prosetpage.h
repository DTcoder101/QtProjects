#ifndef PROSETPAGE_H
#define PROSETPAGE_H

#include <QWizardPage>
#include <QLineEdit>
namespace Ui {
class ProSetPage;
}

class ProSetPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ProSetPage(QWidget *parent = nullptr);
    ~ProSetPage();
    void GetProSetting(QString &proName, QString &proPath);
protected:
   virtual bool isComplete() const;

private:
    void ConnectSignal();
    void SetPathLineEdit();

    template<typename T>
    void ConnectLineEditCompleteChange(QLineEdit* lineEdit, T func)
    {
        connect(lineEdit, &QLineEdit::textEdited, this, func);
    }

private slots:
    void on_pushButton_clicked();

private:
    Ui::ProSetPage *ui;
};

#endif // PROSETPAGE_H
