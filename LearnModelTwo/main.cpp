#include "mainwindow.h"
#include "mystringlist.h"
#include <QApplication>
#include <QTableView>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    QStringList strs;

    strs << "fuck" << "you" << "my beautiful";


    MyStringList str_list_model(strs);
    str_list_model.insertRows(2, 2);

    QTableView* table = new QTableView;
    table->setWindowTitle("Table");
    table->setModel(&str_list_model);

    QListView* list = new QListView;
    list->setWindowTitle("List");
    list->setModel(&str_list_model);

    table->show();
    list->show();

    return a.exec();
}
