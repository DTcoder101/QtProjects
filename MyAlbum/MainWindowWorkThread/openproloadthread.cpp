#include "openproloadthread.h"
#include "protreeitem.h"
#include "ConstDef.h"

#include <QDir>


OpenProLoadThread::OpenProLoadThread(const QString &dir_path, QTreeWidget *pro_tree_widget,
                                     QTreeWidgetItem *root_item, int files_count,
                                     QObject *parent):QThread(parent)
{
    this->dir_path = dir_path;
    this->pro_tree_widget = pro_tree_widget;
    this->pre_item = root_item;
    this->root_item = root_item;
    this->files_count = files_count;
    stop_work = false;
}

void OpenProLoadThread::CancelLoadSlot()
{
    stop_work = true;
}

void OpenProLoadThread::run()
{
    RecursionCreateTreeWidgetItem(dir_path, pro_tree_widget,
                                  &pre_item, root_item, files_count);

    if (stop_work){
        int pro_index = pro_tree_widget->indexOfTopLevelItem(root_item);
        delete pro_tree_widget->takeTopLevelItem(pro_index);

        return;
    }

    emit FinishCreateWork();
}

void OpenProLoadThread::RecursionCreateTreeWidgetItem(const QString &dir_path, QTreeWidget *pro_tree_widget,
                                                      QTreeWidgetItem **pre_item, QTreeWidgetItem *root_item,
                                                      int files_count)
{
    if (stop_work){
        return;
    }

    QDir pro_dir(dir_path);
    pro_dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    pro_dir.setSorting(QDir::Name);
    QFileInfoList files = pro_dir.entryInfoList();

    for(auto file : files){
        if (stop_work){
            return;
        }

        QString file_name = file.fileName();

        if (file.isDir()){
            QTreeWidgetItem* item = CreateTreeItem(file_name, dir_path, root_item, TreeItemType::treeItemDir);

            RecursionCreateTreeWidgetItem(file.filePath(), pro_tree_widget, pre_item, item, files_count);
        }
        else{
            QString suffix = file.completeSuffix();
            if (suffix.toLower() != "jpg" && suffix.toLower() != "png" && suffix.toLower() != "jpeg"){
                continue;
            }

            QTreeWidgetItem* item = CreateTreeItem(file_name, dir_path, root_item, TreeItemType::treeItemPic);

            auto the_pre = dynamic_cast<protreeitem*>(*pre_item);
            the_pre->setNext_item(item);

            dynamic_cast<protreeitem*>(item)->setPre_item(*pre_item);
            *pre_item = item;
        }

        files_count++;
        emit UpdateProgressDialog(files_count);
    }
}

QTreeWidgetItem *OpenProLoadThread::CreateTreeItem(const QString &name, const QString &path, QTreeWidgetItem *root_item, int type)
{
    QDir file_full_path(path);
    protreeitem* item = new protreeitem(root_item, name,
                                        path, root_item, type);
    item->setData(0, Qt::DisplayRole, name);
    //item->setData(0, Qt::DecorationRole, )
    item->setData(0, Qt::ToolTipRole, file_full_path.absoluteFilePath(name));

    return item;
}
