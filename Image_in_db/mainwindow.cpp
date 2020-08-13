#include "mainwindow.h"
#include <thread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(500,500);
    this->setWindowTitle("Image Demo");
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    mainlay=new QStackedLayout;
   mw->setLayout(mainlay);
   mydb=new database;
   win1();
   win2();
   make_menu();
}

void MainWindow::win1()
{
    QWidget *w1=new QWidget;
    w1->setFixedSize(width(),height());
    mainlay->addWidget(w1);
    QVBoxLayout *lay=new QVBoxLayout;
    w1->setLayout(lay);
    QLabel *lb=new QLabel;
    lb->setFixedSize(0.4*width(),0.1*height());
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("<h2 style=color:red>Photo's Title");
    title=new QLineEdit;
    title->setFixedWidth(0.4*width());
    QHBoxLayout *row=new QHBoxLayout;
    lay->addLayout(row);
    row->addWidget(lb);
    row->addWidget(title);
    QPushButton *button=new QPushButton("Upload photo");
    button->setStyleSheet("padding: 2px 5px;"
                                           "font-size: 18px;"
                                           "text-align: center;"
                                           "color: #c95165;"
                                           "background-color: #0a1338;"
                                           "border: none;"
                                           "border-radius: 10px;");
    button->setFixedWidth(0.4*width());
    showlabel=new QLabel;
    showlabel->setFixedSize(0.4*width(),0.5*height());
    showlabel->setStyleSheet("border:2px solid;");
    QHBoxLayout *row1=new QHBoxLayout;
    lay->addLayout(row1);
    row1->addWidget(button);
    row1->addWidget(showlabel);
    connect(button,SIGNAL(clicked(bool)),this,SLOT(localimage()));
    QPushButton *bt=new QPushButton("UPLOAD");
    bt->setStyleSheet("padding: 2px 5px;"
                      "font-size: 18px;"
                      "text-align: center;"
                      "color: #c95165;"
                      "background-color: #0a1338;"
                      "border: none;"
                      "border-radius: 10px;");
    QHBoxLayout *row2=new QHBoxLayout;
    lay->addLayout(row2);
    bt->setFixedWidth(0.3*width());
    row2->setAlignment(Qt::AlignCenter);
    row2->addWidget(bt);
    connect(bt,SIGNAL(clicked(bool)),this,SLOT(uploadslot()));
}

void MainWindow::localimage()
{
    QString fn=QFileDialog::getOpenFileName(this,"Load Image",".","png files (*.png)");
    if(fn.size()==0) return;
    pixmap.load(fn);
    showlabel->setPixmap(pixmap.scaled(showlabel->width(),showlabel->height()));
}

void MainWindow::make_menu()
{
    QMenu *men=new QMenu("PAGE");
    men->addAction("UPLOAD");
    men->addAction("SHOW");
    menuBar()->addMenu(men);
    connect(men,SIGNAL(triggered(QAction *)),this,SLOT(pagechange(QAction *)));
}

void MainWindow::uploadslot()
{
    if(showlabel->pixmap()->isNull() || title->text().isEmpty())
    {
        QMessageBox::critical(this,"Error","Fill all the blanks");
        return;
    }
    mydb->insert(title->text(),pixmap);
}

void MainWindow::win2()
{
    QWidget *w2=new QWidget;
    w2->setFixedSize(width(),height());
    mainlay->addWidget(w2);
    QVBoxLayout *lay=new QVBoxLayout;
    w2->setLayout(lay);
    QPushButton *b=new QPushButton("Preview");
    b->setStyleSheet("padding: 2px 5px;"
                     "font-size: 18px;"
                     "text-align: center;"
                     "color: #c95165;"
                     "background-color: #0a1338;"
                     "border: none;"
                     "border-radius: 10px;");
    lay->addWidget(b);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(previewslot()));
    lbl=new QLabel;
    lbl->setFixedSize(0.4*width(),0.2*height());
    lbl->setAlignment(Qt::AlignCenter);
    lbl->setText("Title");
    lbl->setStyleSheet("border:2px solid;");
    previewlabel=new QLabel;
    previewlabel->setFixedSize(0.4*width(),0.6*height());
    previewlabel->setStyleSheet("border:2px solid;");
    QHBoxLayout *row=new QHBoxLayout;
    lay->addLayout(row);
    row->addWidget(lbl);
    row->addWidget(previewlabel);
}

void MainWindow::previewslot()
{
   QVector <std::tuple<QString,QPixmap>> recs=mydb->get_records();
   for(auto &x:recs)
   {
       lbl->clear();
       previewlabel->clear();
       lbl->setText(std::get<0>(x));
       previewlabel->setPixmap(std::get<1>(x).scaled(previewlabel->width(),previewlabel->height()));
   }
}

MainWindow::~MainWindow()
{
    delete mydb;
}

void MainWindow::pagechange(QAction *a)
{
   if(a->text()=="UPLOAD")
   {
       mainlay->setCurrentIndex(0);
   }
   else
   {
       mainlay->setCurrentIndex(1);
   }
}

