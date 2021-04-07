#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("Drag And Drop Event");
    this->setFixedSize(500,550);
    this->mw=new QWidget();
    this->setCentralWidget(this->mw);
    this->lay=new QVBoxLayout();
    this->mw->setLayout(this->lay);
    this->lay->setAlignment(Qt::AlignTop);
    QWidget *panel=new QWidget();
    panel->setFixedSize(0.96*this->width(),0.4*this->height());
    QHBoxLayout *hl=new QHBoxLayout();
    panel->setLayout(hl);
    draglabel *dl=new draglabel("Drop Here");
    dl->setAlignment(Qt::AlignCenter);
    dl->setFixedSize(this->width(),this->height());
    dl->setStyleSheet("font-size:16px; color:blue; background-color:green;");
    dl->setFixedSize(panel->width(),panel->height());
    dl->setAcceptDrops(true);
    hl->addWidget(dl);
    this->lay->addWidget(panel);
}

MainWindow::~MainWindow()
{
}

