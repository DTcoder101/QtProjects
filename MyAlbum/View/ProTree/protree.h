#ifndef PROTREE_H
#define PROTREE_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class protree;
}

class protree : public QDialog
{
    Q_OBJECT

public:
    explicit protree(QWidget *parent = nullptr);
    ~protree();

public:
    QTreeWidget* GetCustomWidget();

private:
    Ui::protree *ui;

public slots:
    void AddProToTree(const QString& name, const QString& path);
};

#endif // PROTREE_H
