#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QTreeWidget>
#include <QSet>
#include <QAction>
#include <QProgressDialog>

class ImportActionThread;
class OpenProLoadThread;
class SlideShowDialog;

class protreewidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit protreewidget(QWidget *parent = nullptr);
    ~protreewidget();

//create a new tree widget item in project tree widget.
public:
    void AddProToTree(const QString& name, const QString& path);

public slots:
    //open already dir to be a new tree widget item in project tree widget.
    void OpenProToTree(const QString& dir_name, const QString& dir_path);
    //dealing with browse pic signals from picture display dialog.
    void FreshNewSelectItem(QTreeWidgetItem* new_item);

private:
    template<typename CancelSlotPtr>
    void MakeProgressDialog(QProgressDialog** dialog, QString title, int min_range, int max_range, CancelSlotPtr fun)
    {
        *dialog = new QProgressDialog(this);
        connect(*dialog, &QProgressDialog::canceled, this, fun);
       (*dialog)->setWindowTitle(title);
       (*dialog)->setFixedWidth(max_range);
       (*dialog)->setRange(min_range, max_range);
    }

private:
    QSet<QString> set_path;
    QTreeWidgetItem* right_click_item;
    QTreeWidgetItem* current_active_item;
    QTreeWidgetItem* current_display_item;
    QAction* import_action;
    QAction* set_start_action;
    QAction* close_pro_action;
    QAction* slid_show_action;
    QProgressDialog* import_load_dialog;
    QProgressDialog* open_load_dialog;
    std::shared_ptr<ImportActionThread> import_pro_thread;
    std::shared_ptr<OpenProLoadThread> open_pro_thread;
    std::shared_ptr<SlideShowDialog> slide_dlg;
    // SlideShowDialog* slide_dlg;

//the slots to control progress dialog.
private slots:
    //import progress dialog slot.
    void ImportUpdateLoadSlot(int file_count);
    void ImportFinishLoadSlot();
    void ImportCancelLoadSlot();
    //open progress dialog slot.
    void OpenUpdateLoadSlot(int file_count);
    void OpenFinishLoadSlot();
    void OpenCancelLoadSlot();

//the slots to finish works about project tree widget item.
private slots:
    void ImportActionSlot(bool);
    void SetStartActionSlot(bool);
    void CloseProActionSLot(bool);
    void SlideShowActionSLot(bool);
    void ItemPressRight(QTreeWidgetItem *press_item, int);
    void ItemLeftDoubleClick(QTreeWidgetItem *press_item, int);

signals:
    //send to import progress dialog.
    void SigCancelImportLoad();
    //send to open progress dialog.
    void SigCancelOpenLoad();
    //send to picture display dialog.
    void SigFreshPicDisplayArea(QTreeWidgetItem* press_item);
    void SigClosePro(QTreeWidgetItem* close_pro_root);
};

#endif // PROTREEWIDGET_H
