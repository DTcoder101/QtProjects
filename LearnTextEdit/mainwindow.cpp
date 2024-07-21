#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextDocument>
#include <QTextFrame>
#include <QTextCursor>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextDocument* doc = ui->textEdit->document();
    QTextFrame* doc_frame = doc->rootFrame();
    QTextFrameFormat frame_format;
    QBrush brush;
    brush.setColor(Qt::blue);
    frame_format.setBorderBrush(Qt::blue);
    frame_format.setBorder(1.5);
    doc_frame->setFrameFormat(frame_format);

    QTextCursor text_cursor = ui->textEdit->textCursor();
    QTextFrameFormat tilp_format;
    tilp_format.setBorder(2);
    tilp_format.setBorderStyle(QTextFrameFormat::BorderStyle_Dashed);
    tilp_format.setBackground(Qt::lightGray);
    tilp_format.setMargin(10);
    tilp_format.setPadding(5);
    text_cursor.insertFrame(tilp_format);
    text_cursor.insertText(tr("干你！\r\n"));
    text_cursor.insertText(tr("来啊！！\r\n"));




}

MainWindow::~MainWindow()
{
    delete ui;
}
