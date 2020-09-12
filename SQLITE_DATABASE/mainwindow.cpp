#include "mainwindow.h"
#include <QMovie>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mydb=new database;
    this->setFixedSize(400,400);
    this->setWindowTitle("company Database");
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lb=new QLabel;
    lb->setFixedSize(0.98*width(),0.3*height());
    lb->setStyleSheet("border:2px solid;");
    QMovie *m=new QMovie;
    m->setFileName(":/company.gif");
    QSize s(lb->width(),lb->height());
    m->setScaledSize(s);
    lb->setMovie(m);
    lb->movie()->start();
    ml->addWidget(lb);
    n=new QLineEdit;
    id=new QLineEdit;
    did=new QLineEdit;
    sl=new QLineEdit;
    n->setStyleSheet("border:2px solid;"
                     "color:#360315;");
    id->setStyleSheet("border:2px solid;"
                      "color:#360315;");
    did->setStyleSheet("border:2px solid;"
                       "color:#360315;");
    sl->setStyleSheet("border:2px solid;"
                      "color:#360315;");
    QHBoxLayout *row=new QHBoxLayout;
    ml->addLayout(row);
    row->addWidget(n);
    row->addWidget(id);
    row->addWidget(did);
    row->addWidget(sl);
    QPushButton *b=new QPushButton("ADD");
    b->setFixedWidth(0.2*width());
    b->setStyleSheet("color:#910939;"
                     "background-color:#added5;"
                     "border:2px solid;");
    row->addWidget(b);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(addslot()));
    QHBoxLayout *row1=new QHBoxLayout;
    ml->addLayout(row1);
    depid=new QLineEdit;
    dname=new QLineEdit;
    depid->setStyleSheet("border:2px solid;"
                         "color:#360315;");
    dname->setStyleSheet("border:2px solid;"
                         "color:#360315;");
    depid->setFixedWidth(0.3*width());
    dname->setFixedWidth(0.3*width());
    QPushButton *b1=new QPushButton("ADD");
    b1->setFixedWidth(0.2*width());
    b1->setStyleSheet("color:#910939;"
                     "background-color:#added5;"
                     "border:2px solid;");
   row1->addWidget(depid);
   row1->addWidget(dname);
   row1->addWidget(b1);
   connect(b1,SIGNAL(clicked(bool)),this,SLOT(depment()));
   tab=new QTableWidget;
   QStringList lst;
   lst<<"DEP ID"<<"DEP NAME"<<"EMPLOYEES"<<"AVERAGE SALARY";
   tab->setColumnCount(lst.size());
   tab->setHorizontalHeaderLabels(lst);
   tab->setFixedSize(0.95*width(),0.3*height());
   tab->setColumnWidth(0,0.25*tab->width());
   tab->setColumnWidth(1,0.25*tab->width());
   tab->setColumnWidth(2,0.23*tab->width());
   tab->setColumnWidth(3,0.23*tab->width());
   tab->setStyleSheet("border:1px solid;"
                      "font-size:12px"
                      "color:#260305;");
   ml->addWidget(tab);
   connect(this,SIGNAL(renew()),this,SLOT(tabnew()));
}

void MainWindow::newtab()
{
    tab->clearContents();
    QVector <department> deps=mydb->departments();
    tab->setRowCount(deps.size());
    for(int i=0;i<tab->rowCount();i++)
    {
        QTableWidgetItem *it=new QTableWidgetItem;
        it->setText(QString::number(deps[i].get_id()));
        it->setIcon(QIcon(":/id.png"));
        it->setTextAlignment(Qt::AlignCenter);
        QColor c1;
        c1.setNamedColor("#7d0440");
        it->setForeground(c1);
        tab->setItem(i,0,it);
        QTableWidgetItem *it1=new QTableWidgetItem;
        it1->setText(deps[i].getname());
        it1->setIcon(QIcon(":/depicon.png"));
        it1->setTextAlignment(Qt::AlignCenter);
        it1->setForeground(c1);
        tab->setItem(i,1,it1);
        QPushButton *but=new QPushButton("Employees");
        but->setFixedWidth(0.2*width());
        but->setStyleSheet("color:#910939;"
                         "background-color:#added5;"
                         "border:2px solid;");
        but->setProperty("emps",deps[i].get_id());
        connect(but,SIGNAL(clicked(bool())),this,SLOT(employees()));
        but->setFixedWidth(0.95*tab->columnWidth(2));
        tab->setCellWidget(i,2,but);
        QTableWidgetItem *it2=new QTableWidgetItem;
        it2->setForeground(c1);
        double avg=mydb->get_dep_avg_salary(deps[i].getname());
         it2->setTextAlignment(Qt::AlignCenter);
        it2->setText(QString::number(avg));
        tab->setItem(i,3,it2);
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::addslot()
{
    if(n->text().isEmpty() || id->text().isEmpty() || did->text().isEmpty() || sl->text().isEmpty())
    {
        QMessageBox::critical(this,"Error","Fill all the blanks");
        return;
    }
    if(mydb->employeein(id->text().toInt()))
    {
        QMessageBox::critical(this,"EXIST","Employee already exists");
        return;
    }
    mydb->insert_employee(id->text().toInt(),n->text(),did->text().toInt(),sl->text().toDouble());
    emit newtab();
}

void MainWindow::depment()
{
    if(depid->text().isEmpty() || dname->text().isEmpty())
    {
        QMessageBox::critical(this,"Error","Fill all the blanks");
        return;
    }
    if(mydb->departmentin(depid->text().toInt())) return;
    mydb->insert_department(depid->text().toInt(),dname->text());
    emit newtab();
}

void MainWindow::employees()
{
    QPushButton *b=(QPushButton *)sender();
    int id=b->property("emps").toInt();
    QVector <employee> emps=mydb->get_dep_workers(id);
    QString message="<h3 style=color:#910939;>EMPLOYEES</h3><ul>";
    for(auto &x:emps)
    {
        message+="<li>"+x.to_str()+"</li>";
    }
    message+="</ul>";
    QMessageBox::information(this,"WORKERS",message);
}
