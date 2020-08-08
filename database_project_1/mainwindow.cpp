#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mydb=new database("phonebook.db");
    this->setFixedSize(600,600);
    this->setWindowTitle("PhoneBook");
    this->setWindowIcon(QIcon(""));
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    mw->setStyleSheet("background-color:;");
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    make_register_form();
    QPushButton *but=new QPushButton("REGISTER");
    but->setStyleSheet("padding: 3px 5px;"
                       "font-size: 20px;"
                       "text-align: center;"
                       "color: #c95165;"
                       "background-color: #0a1338;"
                       "border: none;"
                       "border-radius: 15px;");
    QPushButton *but1=new QPushButton("CODE SEARCH");
    but1->setStyleSheet("padding: 3px 5px;"
                        "font-size: 20px;"
                        "text-align: center;"
                        "color: #c95165;"
                        "background-color: #0a1338;"
                        "border: none;"
                        "border-radius: 15px;");
    but->setFixedWidth(0.3*width());
    but1->setFixedWidth(0.3*width());
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    r1->addWidget(but);
    r1->addWidget(but1);
    connect(but,SIGNAL(clicked(bool)),this,SLOT(regslot()));
    connect(but1,SIGNAL(clicked(bool)),this,SLOT(codeslot()));
    this->make_search_form();
    tab=new QTableWidget;
    QStringList header;
    header<<"Name"<<"Phone"<<"Address"<<"Code";
    tab->setColumnCount(header.size());
    tab->setHorizontalHeaderLabels(header);
    for(int i=0;i<tab->columnCount();i++)
    {
         tab->setColumnWidth(i,tab->width()/tab->columnCount());
    }
    tab->setFixedSize(width()*0.95,height()*0.4);
    tab->setStyleSheet("border:2px solid;"
                       "border-color:red");
    ml->addWidget(tab);
    connect(this,SIGNAL(add()),this,SLOT(addslot()));
    emit addslot();
 }

void MainWindow::make_search_form()
{
    QHBoxLayout *row=new QHBoxLayout;
    ml->addLayout(row);
    name=new QLineEdit;
    name->setPlaceholderText("Give name you search");
    name->setFixedWidth(0.4*width());
    QPushButton *b1=new QPushButton("SEARCH");
    b1->setStyleSheet("padding: 3px 5px;"
                      "font-size: 20px;"
                      "text-align: center;"
                      "color: #c95165;"
                      "background-color: #0a1338;"
                      "border: none;"
                      "border-radius: 15px;");
    b1->setFixedWidth(0.3*width());
    QLabel *label=new QLabel;
    label->setFixedHeight(0.05*height());
    label->setAlignment(Qt::AlignCenter);
    label->setText("<h3>Search Area</h3>");
    row->addWidget(label);
    row->addWidget(name);
    row->addWidget(b1);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(searchslot()));
}

void MainWindow::make_register_form()
{
    QLabel *l=new QLabel;
    l->setAlignment(Qt::AlignCenter);
    l->setText("<h4>NAME</h4>");
    l->setFixedWidth(0.3*width());
    n=new QLineEdit;
    n->setFixedWidth(0.3*width());
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    r1->addWidget(l);
    r1->addWidget(n);
    QLabel *lb=new QLabel;
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("<h4>ADDRESS</h4>");
    lb->setFixedWidth(0.3*width());
    ad=new QLineEdit;
    ad->setFixedWidth(0.3*width());
    QHBoxLayout *r2=new QHBoxLayout;
    ml->addLayout(r2);
    r2->addWidget(lb);
    r2->addWidget(ad);
    QLabel *ln=new QLabel;
    ln->setAlignment(Qt::AlignCenter);
    ln->setFixedWidth(0.3*width());
    ln->setText("<h4>CODE</h4>");
    cd=new QLineEdit;
    cd->setFixedWidth(0.3*width());
    QHBoxLayout *r3=new QHBoxLayout;
    ml->addLayout(r3);
    r3->addWidget(ln);
    r3->addWidget(cd);
    QLabel *lph=new QLabel;
    lph->setFixedWidth(0.3*width());
    lph->setAlignment(Qt::AlignCenter);
    lph->setText("<h4>PHONE</h4>");
    p=new QLineEdit;
    p->setFixedWidth(0.3*width());
    QHBoxLayout *r4=new QHBoxLayout;
    ml->addLayout(r4);
    r4->addWidget(lph);
    r4->addWidget(p);
}

void MainWindow::addslot()
{
    tab->clearContents();
    QVector <record> recs=mydb->get_records();
    tab->setRowCount(recs.size());
    for(int i=0;i<tab->rowCount();i++)
    {
        tab->setItem(i,0,new QTableWidgetItem(recs.at(i).name));
        tab->setItem(i,1,new QTableWidgetItem(recs.at(i).phone));
        tab->setItem(i,2,new QTableWidgetItem(recs.at(i).address));
        tab->setItem(i,3,new QTableWidgetItem(QString::number(recs.at(i).code)));
    }
}

MainWindow::~MainWindow() {delete mydb;}

void MainWindow::regslot()
{
    if(n->text().isEmpty() || p->text().isEmpty() || cd->text().isEmpty() || ad->text().isEmpty())
    {
        QMessageBox::critical(this,"Error","Please fill all the blanks");
        return;
    }
    if(p->text().length()!=10)
    {
        QMessageBox::critical(this,"ERROR","Phone must contain 10 numbers");
        return;
    }
    if(cd->text().length()!=5)
    {
        QMessageBox::critical(this,"ERROR","Code must contain 5 numbers");
        return;
    }
    if(mydb->record_exist(n->text(),ad->text(),p->text()))
    {
        return;
    }
    mydb->insert(n->text(),ad->text(),p->text(),cd->text().toInt());
    emit addslot();
}
void MainWindow::searchslot()
{
    if(name->text().isEmpty())
    {
        QMessageBox::critical(this,"ERROR","Fill all the blanks");
        return;
    }
    mydb->search(name->text());
}

void MainWindow::codeslot()
{
  showdialog dial(*mydb);
  dial.exec();
}
