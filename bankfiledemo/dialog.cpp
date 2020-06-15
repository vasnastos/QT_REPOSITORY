#include "dialog.h"

dialog::dialog(QVector <QString> &accs)
{
    this->setFixedSize(300,300);
   this->setWindowTitle("NUMBER ENTRANCE");
   mainlayout=new QVBoxLayout;
   this->setLayout(mainlayout);
   number=new QLineEdit;
   QLabel *lb=new QLabel;
   lb->setText("<p style=color:red>ACCOUNT NUMBER</p>");
   lb->setAlignment(Qt::AlignCenter);
   QHBoxLayout *r1=new QHBoxLayout;
   mainlayout->addLayout(r1);
   r1->addWidget(lb);
   r1->addWidget(number);
   but=new QPushButton;
   but->setText("LOGIN");
   QPushButton *cbut=new QPushButton;
   cbut->setText("CANCEL");
   QHBoxLayout *r2=new QHBoxLayout;
   mainlayout->addLayout(r2);
   r2->addWidget(but);
   r2->addWidget(cbut);
   connect(but,SIGNAL(clicked(bool)),this,SLOT(checknum()));
   connect(cbut,SIGNAL(clicked(bool)),this,SLOT(cancelslot()));
   pressed=false;
   numbers=accs;
}

dialog::~dialog() {}

void dialog::checknum()
{
    bool ok=false;
  for(int i=0;i<numbers.size();i++)
  {
      if(number->text()==numbers.at(i))
      {
          connectednumber=numbers.at(i);
          ok=true;
          break;
      }
  }
  if(ok)
  {
      accept();
  }
  else
  {
     reject();
  }
}

void dialog::cancelslot()
{
    pressed=true;
}

QString dialog::getconnect()
{
    return this->connectednumber;
}

bool dialog::forceclose() {return pressed;}
