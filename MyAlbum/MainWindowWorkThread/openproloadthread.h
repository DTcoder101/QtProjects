#ifndef OPENPROLOADTHREAD_H
#define OPENPROLOADTHREAD_H

#include <QThread>
#include <QTreeWidget>

class OpenProLoadThread : public QThread
{
    Q_OBJECT
public:
    explicit OpenProLoadThread(const QString& dir_path, QTreeWidget* pro_tree_widget,
                               QTreeWidgetItem* root_item, int files_count, QObject *parent = nullptr);

public slots:
    void CancelLoadSlot();

protected:
    void run() override;

private:
    void RecursionCreateTreeWidgetItem(const QString& dir_path, QTreeWidget* pro_tree_widget,
                                       QTreeWidgetItem** pre_item, QTreeWidgetItem* root_item,
                                       int files_count);

    QTreeWidgetItem *CreateTreeItem(const QString& name, const QString& path,
                                    QTreeWidgetItem* root_item, int type);
private:
    QString dir_path;
    QTreeWidget* pro_tree_widget;
    QTreeWidgetItem* pre_item;
    QTreeWidgetItem* root_item;
    int files_count;
    bool stop_work;

signals:
    void UpdateProgressDialog(int file_counts);
    void FinishCreateWork();

};

#endif // OPENPROLOADTHREAD_H
