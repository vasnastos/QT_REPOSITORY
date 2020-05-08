#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDesktopWidget *dw=new QDesktopWidget;
    this->setFixedSize(dw->geometry().width()/2,dw->geometry().height()/2);
    this->setWindowTitle("Product database operator");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    tab=new QTabWidget;
    ml->addWidget(tab);
    mydb=new database();
    tab1();
    tab2();
    tab3();
}
void MainWindow::tab1()
{
    QWidget *w1=new QWidget;
    tab->addTab(w1,"Insert_Product");
    QGridLayout *lay=new QGridLayout;
    w1->setLayout(lay);
    id=new QLineEdit;
    id->setPlaceholderText("product_id");
    id->setValidator(new QIntValidator(1,29000));
    cat=new QLineEdit;
    price=new QDoubleSpinBox;
    price->setRange(3.00,10000.00);
    price->setSingleStep(0.25);
    lay->addWidget(id,0,0);
    lay->addWidget(cat,0,1);
    lay->addWidget(price,0,2);
    label=new QLabel;
    label->setStyleSheet("border:solid-2px;");
    QPushButton *b=new QPushButton;
    b->setText("LOAD");
    b->setStyleSheet("background-color:powderblue;");
    lay->addWidget(label,1,0);
    lay->addWidget(b,1,1);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadimage()));
    QPushButton *b1=new QPushButton;
    b1->setText("ADD");
    QPushButton *b2=new QPushButton;
    b2->setText("CLEAR");
    lay->addWidget(b1,2,0);
    lay->addWidget(b2,2,1);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(addslot()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(clearslot()));
}
MainWindow::~MainWindow() {}
void MainWindow::tab2()
{
    QWidget *w2=new QWidget;
    w2->setFixedSize(this->width(),this->height());
    tab->addTab(w2,"OPTIONS");
    QVBoxLayout *vb=new QVBoxLayout;
    w2->setLayout(vb);
    QPushButton *b=new QPushButton;
    b->setText("SEARCH");
    table=new QTableWidget;
    ch1=new QDoubleSpinBox;
    ch2=new QDoubleSpinBox;
    ch1->setRange(mydb->min(),mydb->max());
    ch2->setRange(mydb->min(),mydb->max());
    QHBoxLayout *r1=new QHBoxLayout;
    vb->addLayout(r1);
    r1->addWidget(ch1);
    r1->addWidget(ch2);
    r1->addWidget(b);
    connect(b,SIGNAL(clicked()),this,SLOT(show_product()));
    QStringList header;
    header<<"ID"<<"CATEGORY"<<"PRICE"<<"PREVIEW";
    table->setColumnCount(header.size());
    table->setHorizontalHeaderLabels(header);
    vb->addWidget(table);
}
void MainWindow::tab3()
{
    QWidget *w3;
    w3=new QWidget;
    w3->setFixedSize(this->width(),this->height());
    tab->addTab(w3,"SHOW_PRODUCTS");
    QVBoxLayout *vb=new QVBoxLayout;
    w3->setLayout(vb);
    QHBoxLayout *r1=new QHBoxLayout;
    vb->addLayout(r1);
    QLabel *l=new QLabel;
    l->setFixedSize(this->width()/2,100);
    l->setAlignment(Qt::AlignCenter);
    l->setStyleSheet("background-color:yellow;");
    l->setText("<p style=color:red>CATEGORY OF PRODUCTS</p>");
    QPushButton *but=new QPushButton;
    but->setText("SHOW");
    but->setFixedSize(l->width(),l->height());
    r1->addWidget(l);
    r1->addWidget(but);
    connect(but,SIGNAL(clicked(bool)),this,SLOT(catalog()));
    tw=new QTableWidget;
    QStringList header;
    header<<"ID"<<"CATEGORY"<<"PRICE"<<"PREVIEW";
    tw->setColumnCount(header.size());
    tw->setHorizontalHeaderLabels(header);
    vb->addWidget(table);
}
void MainWindow::clearslot()
{
    id->setText("");
    price->setValue(3.0);
    cat->setText("");
    label->clear();
}
void MainWindow::loadimage()
{
    QString fn=QFileDialog::getOpenFileName(this,"CHOOSE PHOTO",".","png files (*.PNG)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"ERROR","<p style=color:red>No photo choose</p>");
        return;
    }
    pix.load(fn);
    label->setPixmap(pix.scaled(label->size()));
}
void MainWindow::addslot()
{
  if(id->text().isEmpty() || cat->text().isEmpty() || pix.isNull())
  {
      QMessageBox::critical(this,"ERROR","Fill all the blanks");
      return;
  }
  if(mydb->is_in(id->text().toInt()))
  {
      QMessageBox::critical(this,"error",id->text()+" already exists in database");
      return;
  }

  product p(id->text().toInt(),pix,cat->text(),price->value());
  mydb->insert_product(p);
}
void MainWindow::show_product()
{
    QVector<product> products=mydb->getbyprice(ch1->value(),ch2->value());
    table->setRowCount(products.size());
    for(int i=0;i<table->rowCount();i++)
    {
       table->setItem(i,0,new QTableWidgetItem(QString::number(products[i].getid())));
       table->setItem(i,1,new QTableWidgetItem(products[i].getcategory()));
       table->setItem(i,2,new QTableWidgetItem(QString::number(products[i].getprice())));
       QLabel *lab=new QLabel;
       table->setRowHeight(i,0.03*this->height());
       lab->setPixmap(products[i].getimage().scaled(lab->size()));
       table->setCellWidget(i,3,lab);
    }
}
void MainWindow::catalog()
{
    QVector<product> products=mydb->getproducts();
    tw->setRowCount(products.size());
    for(int i=0;i<table->rowCount();i++)
    {
       tw->setItem(i,0,new QTableWidgetItem(QString::number(products[i].getid())));
       tw->setItem(i,1,new QTableWidgetItem(products[i].getcategory()));
       tw->setItem(i,2,new QTableWidgetItem(QString::number(products[i].getprice())));
       QLabel *lab=new QLabel;
       tw->setRowHeight(i,0.03*this->height());
       lab->setPixmap(products[i].getimage().scaled(lab->size()));
       tw->setCellWidget(i,3,lab);
    }
}
