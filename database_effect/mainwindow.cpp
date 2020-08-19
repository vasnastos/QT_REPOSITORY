#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mdb=new database;
    this->setFixedSize(600,600);
    this->setWindowTitle("Update Window");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    n=new QLineEdit;
    n->setPlaceholderText("Product Name");
    n->setFixedWidth(0.25*width());
    code=new QLineEdit;
    code->setPlaceholderText("Product Code");
    code->setFrame(true);
    price=new QLineEdit;
    price->setPlaceholderText("Product Price");
    QHBoxLayout *row=new QHBoxLayout;
    ml->addLayout(row);
    row->addWidget(n);
    row->addWidget(code);
    row->addWidget(price);
    prev=new QLabel;
    prev->setFixedSize(this->width()*0.4,this->height()*0.4);
    prev->setStyleSheet("border:2px solid;");
    QPushButton *load=new QPushButton("LOAD");
    load->setStyleSheet("padding: 2px 5px;"
                        "font-size: 19px;"
                        "text-align: center;"
                        "color: #b30046;"
                        "background-color: #e6ffff;"
                        "border: 1px solid black;"
                        "border-radius: 2px solid black;"
                        "font-weight: bold;");
    load->setFixedWidth(0.2*width());
    QPushButton *upload=new QPushButton("UPLOAD");
    upload->setStyleSheet("padding: 2px 5px;"
                          "font-size: 19px;"
                          "text-align: center;"
                          "color: #b30046;"
                          "background-color: #e6ffff;"
                          "border: 1px solid black;"
                          "border-radius: 2px solid black;"
                          "font-weight: bold;");
    upload->setFixedWidth(0.2*width());
    QHBoxLayout *row1=new QHBoxLayout;
    ml->addLayout(row1);
    row1->addWidget(prev);
    row1->addWidget(load);
    row1->addWidget(upload);
    tab=new QTableWidget;
    tab->setFixedSize(0.95*width(),0.5*height());
    tab->setStyleSheet("border:1px solid;");
    QStringList lst;
    lst<<"Name"<<"Id"<<"Picture"<<"Price";
    tab->setColumnCount(lst.size());
    tab->setColumnWidth(0,0.2*tab->width());
    tab->setColumnWidth(1,0.2*tab->width());
    tab->setColumnWidth(2,0.4*tab->width());
    tab->setColumnWidth(3,0.17*tab->width());
    tab->setHorizontalHeaderLabels(lst);
    ml->addWidget(tab);
    connect(load,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(upload,SIGNAL(clicked(bool)),this,SLOT(uploadslot()));
    connect(this,SIGNAL(recordadded()),this,SLOT(renew()));
    emit renew();
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"Upload product image",".","image (*.png)");
    if(fn.size()==0)
    {
        return;
    }
    pix.load(fn);
    prev->setPixmap(pix.scaled(prev->width(),prev->height()));
}

void MainWindow::uploadslot()
{
   if(n->text().isEmpty() || price->text().isEmpty() || code->text().isEmpty() || prev->pixmap()->isNull())
   {
       QMessageBox::critical(this,"Error","<p style=color:red>Fill all the blanks</p>");
       return;
   }
   mdb->insert(n->text(),code->text(),pix,price->text().toDouble());
   emit renew();
}

void MainWindow::renew()
{
    tab->clearContents();
    QVector <product> prs=mdb->products();
    tab->setRowCount(prs.size());
    for(int i=0;i<prs.size();i++)
    {
        tab->setRowHeight(i,0.4*tab->height());
        tab->setItem(i,0,new QTableWidgetItem(prs[i].name));
        tab->setItem(i,1,new QTableWidgetItem(prs[i].id));
        QLabel *lb=new QLabel;
        lb->setFixedSize(tab->columnWidth(2),tab->rowHeight(i));
        lb->setPixmap(prs[i].pix.scaled(lb->width(),lb->height()));
        tab->setCellWidget(i,2,lb);
        QTableWidgetItem *it=new QTableWidgetItem;
        it->setForeground(Qt::red);
        it->setText(QString::number(prs[i].price));
        tab->setItem(i,3,it);
    }
}
