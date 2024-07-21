#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mydelegate.h"

#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Mydelegate* delegate = new Mydelegate(this);
    QTableView* table = new QTableView(this);
    QStandardItemModel* model = new QStandardItemModel(7, 4, this);

    for (uint32_t row = 0; row < 7; row++)
    {
        for (uint32_t column = 0; column < 4; column++)
        {
            QStandardItem* item = new QStandardItem(QString("%1").arg(row * 4 + column));
            model->setItem(row, column, item);
        }
    }

    table->setModel(model);
    table->setItemDelegate(delegate);
    setCentralWidget(table);
    this->resize(400, 300);

    table2 = new QTableView();
    table2->setModel(model);
    table2->resize(400, 300);
    table2->show();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete table2;
}
