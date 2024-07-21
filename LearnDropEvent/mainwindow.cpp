#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMimeData>
#include <QFile>
#include <QTextStream>
#include <QUrl>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
    ui->textEdit->setAcceptDrops(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QMimeData* mimeData = event->mimeData();
    if (mimeData->hasUrls())
    {
        auto ret = mimeData->urls();

        if (!ret[0].isEmpty())
        {
            QString flie_path = ret[0].toLocalFile();
            QFile file(flie_path);

            if (file.open(QIODevice::ReadOnly))
            {
                QTextStream in(&file);
                ui->textEdit->setText(in.readAll());
            }
        }
    }
    else
    {
        event->ignore();
    }
}
