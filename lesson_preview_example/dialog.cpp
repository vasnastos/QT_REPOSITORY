#include "dialog.h"

dialog::dialog(database &d,QWidget *p):QDialog(p)
{
    dialdb=&d;
   this->setFixedSize(300,500);
    ml=new QVBoxLayout;
    lay=new QHBoxLayout;
    this->setLayout(ml);
    QLabel *des=new QLabel("<h2 style=color:blue; text-align:center;>SELECT A LESSON FROM DATABASE</h2>");
    des->setFixedSize(0.95 * width(),0.2*height());
    ml->addWidget(des);
    QLabel *label=new QLabel;
    label->setFixedSize(0.95*width(),0.30 * height());
    QPixmap pix(":/select.png");
    label->setPixmap(pix.scaled(label->width(),label->height()));
    ml->addWidget(label);
    ml->addLayout(lay);
    bx=new QComboBox;
    bx->addItems(dialdb->getlessons());
    lay->addWidget(bx);
    QPushButton *b=new QPushButton;
    b->setText("Select");
    lay->addWidget(b);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(selectslot()));
}

dialog::~dialog() {dialdb=nullptr;}

void dialog::selectslot()
{
  QString les=bx->currentText();
  dts=dialdb->get_lesson_dets(les);
  selectedlesson=les;
  this->close();
}

QVector <dets> dialog::getdetsvector() {return dts;}

QString dialog::getselectedlesson() {return selectedlesson;}
