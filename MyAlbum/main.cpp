#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss(":/style/style.qss");
    if (qss.open(QFile::ReadOnly)){
        QString style = QLatin1StringView(qss.readAll());
        qss.close();
        a.setStyleSheet(style);
    }else{
        qDebug() << "open qss filed";
        return 0;
    }

    MainWindow w;
    w.setWindowTitle("Album");
    QList scrs = QGuiApplication::screens();

    w.setMinimumSize(scrs.at(0)->size().width() - 500,
                     scrs.at(0)->size().height() - 300);
    w.showMaximized();
    return a.exec();
}
