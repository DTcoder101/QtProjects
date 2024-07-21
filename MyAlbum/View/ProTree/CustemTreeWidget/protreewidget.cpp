#include "protreewidget.h"
#include "protreeitem.h"
#include "ConstDef.h"
#include "qmenu.h"
#include "importactionthread.h"
#include "openproloadthread.h"
#include "removeprodialog.h"
#include "slideshowdialog.h"

#include <QDir>
#include <QHeaderView>
#include <QGuiApplication>
#include <QFileDialog>


protreewidget::protreewidget(QWidget *)
{
    import_pro_thread = nullptr;
    open_pro_thread = nullptr;
    current_active_item = nullptr;
    right_click_item = nullptr;
    import_load_dialog = nullptr;
    slide_dlg = nullptr;

    this->header()->hide();

    connect(this, &protreewidget::itemPressed, this, &protreewidget::ItemPressRight);
    connect(this, &protreewidget::itemDoubleClicked, this, &protreewidget::ItemLeftDoubleClick);

    import_action = new QAction(tr("导入文件"), this);
    set_start_action = new QAction(tr("设置启动项"), this);
    close_pro_action = new QAction(tr("关闭项目"), this);
    slid_show_action = new QAction(tr("轮播"), this);

    connect(import_action, &QAction::triggered, this, &protreewidget::ImportActionSlot);
    connect(set_start_action, &QAction::triggered, this, &protreewidget::SetStartActionSlot);
    connect(close_pro_action, &QAction::triggered, this, &protreewidget::CloseProActionSLot);
    connect(slid_show_action, &QAction::triggered, this, &protreewidget::SlideShowActionSLot);
}

protreewidget::~protreewidget()
{

}

void protreewidget::AddProToTree(const QString& name, const QString& path)
{
    QDir dir(path);
    QString file_all_path = dir.absoluteFilePath(name);
    if (set_path.find(file_all_path) != set_path.end()){
        return;
    }

    set_path.insert(file_all_path);

    QFont now_font;
    now_font.setBold(false);
    if (current_active_item){
        current_active_item->setFont(0, now_font);
    }

    protreeitem* item = new protreeitem(this, name, path, TreeItemType::treeItemPro);
    item->setData(0, Qt::DisplayRole, name);
    //item->setData(0, Qt::DecorationRole, );
    item->setData(0, Qt::ToolTipRole, file_all_path);

    current_active_item = item;
    now_font.setBold(true);
    current_active_item->setFont(0, now_font);

    this->addTopLevelItem(item);
}

void protreewidget::OpenProToTree(const QString &dir_name, const QString &dir_path)
{
    AddProToTree(dir_name, dir_path);

    MakeProgressDialog(&open_load_dialog, tr("打开中..."), 0, PRO_IMPROT_LOAD_WIDTH, &protreewidget::OpenCancelLoadSlot);

    QDir dir_pos(dir_path);
    QString dir_full_path = dir_pos.absoluteFilePath(dir_name);
    open_pro_thread = std::make_shared<OpenProLoadThread>(std::ref(dir_full_path), this, current_active_item, 0);
    open_pro_thread->start();

    connect(open_pro_thread.get(), &OpenProLoadThread::UpdateProgressDialog, this, &protreewidget::OpenUpdateLoadSlot);
    connect(open_pro_thread.get(), &OpenProLoadThread::FinishCreateWork, this, &protreewidget::OpenFinishLoadSlot);
    connect(open_load_dialog, &QProgressDialog::canceled, this, &protreewidget::OpenCancelLoadSlot);

    open_load_dialog->exec();
}

void protreewidget::FreshNewSelectItem(QTreeWidgetItem *new_item)
{
    setCurrentItem(new_item);
}

void protreewidget::ItemPressRight(QTreeWidgetItem *press_item, int)
{
    if (QGuiApplication::mouseButtons() != Qt::RightButton){
        return;
    }

    if (press_item->type() != TreeItemType::treeItemPro){
        return;
    }

    right_click_item = press_item;

    QMenu right_menu(this);
    right_menu.addAction(import_action);
    right_menu.addAction(set_start_action);
    right_menu.addAction(close_pro_action);
    right_menu.addAction(slid_show_action);
    right_menu.exec(QCursor::pos());
}

void protreewidget::ItemLeftDoubleClick(QTreeWidgetItem *press_item, int)
{
    if (QGuiApplication::mouseButtons() != Qt::LeftButton){
        return;
    }

    emit SigFreshPicDisplayArea(press_item);
}

void protreewidget::ImportActionSlot(bool)
{
    if (right_click_item == nullptr){
        return;
    }

    QString path = dynamic_cast<protreeitem*>(right_click_item)->getPath();
    QString name = dynamic_cast<protreeitem*>(right_click_item)->getName();

    QFileDialog file_select;
    file_select.setFileMode(QFileDialog::Directory);
    file_select.setWindowTitle(tr("选择导入的文件夹"));
    file_select.setDirectory(path);
    QStringList file_names;
    if (file_select.exec()){
        file_names = file_select.selectedFiles();
    }
    if (file_names.size() <= 0){
        return;
    }

    MakeProgressDialog(&import_load_dialog, tr("加载中..."), 0, PRO_IMPROT_LOAD_WIDTH, &protreewidget::ImportCancelLoadSlot);

    QString import_path = file_names.at(0);
    QDir dir_path(path);
    QString dist_path = dir_path.absoluteFilePath(name);
    import_pro_thread = std::make_shared<ImportActionThread>(std::ref(import_path), std::ref(dist_path),
                                               right_click_item, 0, this, right_click_item);
    import_pro_thread->start();

    connect(import_pro_thread.get(), &ImportActionThread::UpdateFileCount, this, &protreewidget::ImportUpdateLoadSlot);
    connect(import_pro_thread.get(), &ImportActionThread::LoadFileFinish, this, &protreewidget::ImportFinishLoadSlot);
    connect(this, &protreewidget::SigCancelImportLoad, import_pro_thread.get(), &ImportActionThread::CancelLoad);

    import_load_dialog->exec();
}

void protreewidget::ImportUpdateLoadSlot(int file_count)
{
    import_load_dialog->setValue(file_count % PRO_IMPROT_LOAD_WIDTH);
}

void protreewidget::ImportFinishLoadSlot()
{
    import_load_dialog->setValue(PRO_IMPROT_LOAD_WIDTH);

    disconnect(import_pro_thread.get(), &ImportActionThread::UpdateFileCount, this, &protreewidget::ImportUpdateLoadSlot);
    disconnect(import_pro_thread.get(), &ImportActionThread::LoadFileFinish, this, &protreewidget::ImportFinishLoadSlot);

    import_load_dialog->deleteLater();
}

void protreewidget::ImportCancelLoadSlot()
{
    //send the cancel signal to import action load work thread.
    emit SigCancelImportLoad();

    import_load_dialog->deleteLater();
}

void protreewidget::OpenUpdateLoadSlot(int file_count)
{
    open_load_dialog->setValue(file_count % PRO_IMPROT_LOAD_WIDTH);
}

void protreewidget::OpenFinishLoadSlot()
{
    open_load_dialog->setValue(PRO_IMPROT_LOAD_WIDTH);

    disconnect(open_pro_thread.get(), &OpenProLoadThread::UpdateProgressDialog, this, &protreewidget::OpenUpdateLoadSlot);
    disconnect(open_pro_thread.get(), &OpenProLoadThread::FinishCreateWork, this, &protreewidget::OpenFinishLoadSlot);

    open_load_dialog->deleteLater();
}

void protreewidget::OpenCancelLoadSlot()
{
    emit SigCancelOpenLoad();

    open_load_dialog->deleteLater();
}

void protreewidget::SetStartActionSlot(bool)
{
    if (!right_click_item){
        return;
    }

    QFont now_font;
    now_font.setBold(false);
    if (current_active_item){
        current_active_item->setFont(0, now_font);
    }
    current_active_item = right_click_item;
    now_font.setBold(true);
    current_active_item->setFont(0, now_font);
}

void protreewidget::CloseProActionSLot(bool)
{
    RemoveProDialog remove_dlg;
    if (remove_dlg.exec() == QDialog::Rejected){
        return;
    }

    emit SigClosePro(right_click_item);

    QString delete_path = dynamic_cast<protreeitem*>(right_click_item)->getPath();
    QString delete_name = dynamic_cast<protreeitem*>(right_click_item)->getName();

    QDir delete_dir(delete_path);
    QString delete_full_path = delete_dir.absoluteFilePath(delete_name);

    set_path.remove(delete_full_path);

    if (remove_dlg.IsDeleteFiles()){
        QDir full_delete(delete_full_path);
        full_delete.removeRecursively();
    }

    if (current_active_item == right_click_item){
        current_active_item = nullptr;
    }
    int pro_index = indexOfTopLevelItem(right_click_item);
    delete takeTopLevelItem(pro_index);
    right_click_item = nullptr;
}

void protreewidget::SlideShowActionSLot(bool)
{
    if (right_click_item == nullptr){
        return;
    }

    auto* first_slide_show = dynamic_cast<protreeitem*>(right_click_item)->getNext_item();

    slide_dlg = std::make_shared<SlideShowDialog>(first_slide_show);
    slide_dlg->setWindowFlags(Qt::WindowType::Dialog | Qt::WindowType::FramelessWindowHint);
    slide_dlg->showMaximized();
    slide_dlg->setModal(true);
}
