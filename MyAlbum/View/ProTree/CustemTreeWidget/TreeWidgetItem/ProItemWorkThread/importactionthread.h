#ifndef IMPORTACTIONTHREAD_H
#define IMPORTACTIONTHREAD_H

#include <QThread>
#include <QTreeWidgetItem>

class ImportActionThread : public QThread
{
    Q_OBJECT
public:
    explicit ImportActionThread(QString& src_path, QString& dist_path,
                                QTreeWidgetItem* parent_item, int file_count, QTreeWidget* pro_tree_widget,
                                QTreeWidgetItem* root, QObject* parent = nullptr);

    ~ImportActionThread();

protected:
    void run() override;

private:
    void CreateProTree(const QString& src_path, const QString& dist_path,
                       QTreeWidgetItem *parent_item, int file_count,
                       QTreeWidget *pro_tree_widget, QTreeWidgetItem *root,
                       QTreeWidgetItem **pre_item);

    QTreeWidgetItem *CreateTreeItem(QTreeWidgetItem* parent, const QString& name, const QString& path,
                                    QTreeWidgetItem* root_nood, int type);
private:
    QString src_path;
    QString dist_path;
    QTreeWidgetItem* parent_item;
    int file_count;
    QTreeWidget* pro_tree_widget;
    QTreeWidgetItem* root;
    QTreeWidgetItem* pre_item;
    bool work_stop;

public slots:
    void CancelLoad();
signals:
    void UpdateFileCount(int file_count);
    void LoadFileFinish();
};

#endif // IMPORTACTIONTHREAD_H
