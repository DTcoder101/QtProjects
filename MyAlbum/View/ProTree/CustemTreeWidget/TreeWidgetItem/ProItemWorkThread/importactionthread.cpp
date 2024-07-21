#include "importactionthread.h"
#include "protreeitem.h"
#include "ConstDef.h"

#include <QDir>


ImportActionThread::ImportActionThread( QString& src_path, QString& dist_path,
                                       QTreeWidgetItem *parent_item, int file_count,
                                       QTreeWidget *pro_tree_widget, QTreeWidgetItem *root,
                                       QObject *parent):QThread(parent)
{
    this->src_path = src_path;
    this->dist_path = dist_path;
    this->parent_item = parent_item;
    this->file_count = file_count;
    this->pro_tree_widget = pro_tree_widget;
    this->root = root;
    this->pre_item = root;
    work_stop = false;
}

ImportActionThread::~ImportActionThread()
{

}

void ImportActionThread::run()
{
    CreateProTree(src_path, dist_path, parent_item,
                  file_count, pro_tree_widget, root, &pre_item);
    if (work_stop){
        QDir dis_dir(dist_path);
        dis_dir.removeRecursively();

        int pro_index = pro_tree_widget->indexOfTopLevelItem(root);
        delete pro_tree_widget->takeTopLevelItem(pro_index);

        return;
    }

    emit LoadFileFinish();
}

void ImportActionThread::CreateProTree(const QString& src_path, const QString& dist_path,
                                       QTreeWidgetItem *parent_item, int file_count,
                                       QTreeWidget *pro_tree_widget, QTreeWidgetItem *root,
                                       QTreeWidgetItem **pre_item)
{
    if (work_stop){
        return;
    }

    bool need_copy = true;
    if (src_path == dist_path){
        need_copy = false;
    }

    QDir import_dir(src_path);
    import_dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    import_dir.setSorting(QDir::Name);
    QFileInfoList all_file_dir = import_dir.entryInfoList();

    for(auto file_dir : all_file_dir){
        if (work_stop){
            return;
        }

        QDir dist_path_dir(dist_path);
        QString dist_file_path = dist_path_dir.absoluteFilePath(file_dir.fileName());

        if (file_dir.isDir()){
            //make this dir if it's not exists in dist folder.
            QDir sub_dir(dist_file_path);
            if (!sub_dir.exists()){
                bool ret = sub_dir.mkpath(dist_file_path);
                if (!ret){
                    continue;
                }
            }

            //the folder is exists, create new dir item for the tree widget.
            QTreeWidgetItem *item = CreateTreeItem(parent_item, file_dir.fileName(),
                           dist_file_path, root, TreeItemType::treeItemDir);

            //create tree item recursion, if this is dir in src folder.
            CreateProTree(file_dir.absoluteFilePath(), dist_file_path, item,
                          file_count, pro_tree_widget, root, pre_item);
        }
        else{
            //make a filter, just need picture in there.
            QString suffix = file_dir.completeSuffix();
            if (suffix.toLower() != "png" && suffix.toLower() != "jpg" && suffix.toLower() != "jpeg"){
                continue;
            }

            if (!need_copy){
                continue;
            }

            //move the picture from src dir to dis dir.
            if (!QFile::copy(file_dir.absoluteFilePath(), dist_file_path)){
                continue;
            }

            //the picture is exists in src dir, create new pic item for the tree widget.
            QTreeWidgetItem* item = CreateTreeItem(parent_item, file_dir.fileName(),
                                               dist_path, root, TreeItemType::treeItemPic);

            //link the new PIC tree item to item list.
            //'pre_item' is local variable to recorded the last item that read from src dir.
            auto* pre_pro_item = dynamic_cast<protreeitem*>(*pre_item);
            pre_pro_item->setNext_item(item);
            //set this item's previous item,
            dynamic_cast<protreeitem*>(item)->setPre_item(*pre_item);
            //update 'pre_item' to this item for next loop.
            *pre_item = item;
        }

        //emit signal to pro_tree_widget to updata progress dialog.
        file_count++;
        emit UpdateFileCount(file_count);
    }
}

QTreeWidgetItem *ImportActionThread::CreateTreeItem(QTreeWidgetItem *parent, const QString &name,
                                                    const QString &path, QTreeWidgetItem *root_nood, int type)
{
    QDir file_full_path(path);
    protreeitem* item = new protreeitem(parent, name, path, root_nood, type);
    item->setData(0, Qt::DisplayRole, name);
    //item->setData(0, Qt::DecorationRole);
    item->setData(0, Qt::ToolTipRole, file_full_path.absoluteFilePath(name));

    return item;
}

void ImportActionThread::CancelLoad()
{
    work_stop = true;
}
