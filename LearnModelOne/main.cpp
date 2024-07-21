#include "mainwindow.h"

#include <QApplication>
#include <QSplitter>
#include <QFileSystemModel>
#include <QDir>
#include <QTreeView>
#include <QListView>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    QSplitter* sqpliter = new QSplitter;
    QFileSystemModel* model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());

    QTreeView* tree = new QTreeView(sqpliter);
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));

    QListView* list = new QListView(sqpliter);
    list->setModel(model);
    list->setRootIndex(model->index(QDir::currentPath()));

    sqpliter->resize(800, 1000);
    sqpliter->show();

    return a.exec();
}
