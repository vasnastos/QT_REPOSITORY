#include "showdialog.h"

showdialog::showdialog(database &d,QWidget *p):QDialog(p)
{
   this->setFixedSize(400,400);
    this->setWindowTitle("Show Window");
    lay=new QVBoxLayout;
    QLabel *label=new QLabel;
    label->setAlignment(Qt::AlignRight);
    label->setFixedWidth(0.35*this->width());
    label->setText("<h4 style=color:blue>Code Search</h4>");
    this->setLayout(lay);
    bx=new QComboBox;
    db=&d;
    bx->setFixedWidth(0.35*this->width());
    bx->addItems(db->codes());
    QHBoxLayout *r1=new QHBoxLayout;
    lay->addLayout(r1);
    r1->addWidget(label);
    r1->addWidget(bx);
    connect(bx,SIGNAL(activated(QString)),this,SLOT(comboslot(QString)));
    tb=new QTableWidget;
    tb->setFixedSize(0.95*this->width(),0.80*height());
    tb->setStyleSheet("border:2px solid;");
    QStringList list;
    list<<"Name"<<"Address"<<"Phone";
    tb->setColumnCount(list.size());
    tb->setHorizontalHeaderLabels(list);
    for(int i=0;i<tb->columnCount();i++)
    {
        tb->setColumnWidth(i,0.96*tb->width()/tb->columnCount());
    }
    lay->addWidget(tb);
}

void showdialog::comboslot(QString text)
{
   tb->clearContents();
   QVector <record> recs=db->get_records();
   int cnt=0;
   for(auto &x:recs)
   {
       if(x.code==text.toInt())
       {
           cnt++;
       }
   }
   tb->setRowCount(cnt);
   int i=0;
   for(auto &x:recs)
   {
       if(x.code==text.toInt())
       {
           tb->setItem(i,0,new QTableWidgetItem(x.name));
           tb->setItem(i,1,new QTableWidgetItem(x.address));
           tb->setItem(i,2,new QTableWidgetItem(x.phone));
           i++;
       }
   }
}
