#include "dialog.h"

dialog::dialog(database &getdb)
{
    db=&getdb;
   this->setWindowTitle("Login window");
   this->setFixedSize(300,300);
    this->setWhatsThis("Σύνδεση στο σύστημα για εισαγωγή βαθμολογίας σε μάθημα");
    this->setWindowIconText("Σύνδεση στην σελίδα εισαγωγής βαθμολογιών");
   lay=new QVBoxLayout;
   this->setLayout(lay);
   QLabel *label1=new QLabel;
   QLabel *label2=new QLabel;
   label1->setText("<h3><p style=color:DarkSlateGrey>USERNAME</p></h3>");
   label2->setText("<h3><p style=color:DarkSlateGrey>PASSWORD</p></h3>");
   username=new QLineEdit;
   password=new QLineEdit;
   password->setEchoMode(QLineEdit::Password);
   QHBoxLayout *row1=new QHBoxLayout;
   QHBoxLayout *row2=new QHBoxLayout;
   lay->addLayout(row1);
   lay->addLayout(row2);
   row1->addWidget(label1);
   row1->addWidget(username);
   row2->addWidget(label2);
   row2->addWidget(password);
   QPushButton *pb=new QPushButton;
   QPushButton *pb1=new QPushButton;
   pb->setText("LOGIN");
   pb1->setText("CANCEL");
   QHBoxLayout *r1=new QHBoxLayout;
   lay->addLayout(r1);
   r1->addWidget(pb);
   r1->addWidget(pb1);
   connect(pb,SIGNAL(clicked(bool)),this,SLOT(checkcredentials()));
   connect(pb1,SIGNAL(clicked(bool)),this,SLOT(cancelslot()));
   this->cancelbutton=false;
}

dialog::~dialog() {}
void dialog::checkcredentials()
{
   if(db->credentialsexist(username->text(),password->text()))
   {
       this->accept();
   }
   else
    {
      this->reject();
   }
}
bool dialog::enablecancelbutton() {return this->cancelbutton;}
void dialog::cancelslot()
{
    this->cancelbutton=true;
    this->close();
}
