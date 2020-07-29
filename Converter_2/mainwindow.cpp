#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,600);
    this->setWindowTitle("INCH HANDLER");
    this->setWindowIcon(QIcon(":/converter.png"));
    mw=new QWidget;
    mw->setStyleSheet("background-color:#deeaee;");
    this->setCentralWidget(mw);
    QLabel *label=new QLabel;
    label->setFixedSize(0.95*width(),0.4*height());
    QPixmap pix(":/central.png");
    label->setPixmap(pix.scaled(label->width(),label->height()));
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    ml->addWidget(label);
    QHBoxLayout *lay=new QHBoxLayout;
    ml->addLayout(lay);
    QLabel *in1=new QLabel;
    in1->setAlignment(Qt::AlignCenter);
    in1->setStyleSheet("background-color:red;");
    in1->setText("<h4>Insert a value</h4>");
    f=new QDoubleSpinBox;
    f->setToolTip("Value you want to convert");
    f->setSingleStep(0.25);
    QStringList list;
    list<<"m"<<"cm"<<"mm"<<"inch"<<"feet"<<"yard";
    bx=new QComboBox;
    bx->addItems(list);
    lay->addWidget(in1);
    lay->addWidget(f);
    lay->addWidget(bx);
    to=new QLineEdit;
    to->setStyleSheet("QLineEdit {  border: 2px solid gray;"
                      "border-radius: 3px;}");
    to->setFixedWidth(0.33 * width());
    tbx=new QComboBox;
    QLabel *in2=new QLabel;
    in2->setAlignment(Qt::AlignCenter);
    in2->setText("<h4>Results</h4>");
    in2->setStyleSheet("background-color:red;");
    tbx->addItems(list);
    QHBoxLayout *lay1=new QHBoxLayout;
    ml->addLayout(lay1);
    lay1->addWidget(in2);
    lay1->addWidget(to);
    lay1->addWidget(tbx);
    connect(tbx,SIGNAL(activated(QString)),this,SLOT(act(QString)));
    make_menu();
}

void MainWindow::make_menu()
{
    QMenu *men=new QMenu("EDIT");
    men->addAction(QIcon(":/about.png"),"ABOUT");
    men->addAction(QIcon(":/help.png"),"HELP");
    QMenu *bck=new QMenu("Background settings");
    men->addMenu(bck);
    bck->addAction("LavenderBlush");
    bck->addAction("LightSalmon");
    bck->addAction("MediumOrchid");
    menuBar()->addMenu(men);
    connect(men,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
    connect(bck,SIGNAL(triggered(QAction *)),this,SLOT(colorslot(QAction *)));
}

MainWindow::~MainWindow() {}

void MainWindow::act(QString x)
{
    double result=0.0;
    double data=f->value();
    QString val=bx->currentText();
    if(val==x)
    {
        QMessageBox::warning(this,"Warning","<p style=blue>Conversion to same type</p>");
        to->setText("Result:"+QString::number(f->value(),'f',3));
        return;
    }
    else if(val=="m" && x=="cm")
    {
      result=data*100.0;
    }
    else if(val=="m" && x=="mm")
    {
        result=data*1000.0;
    }
    else if(val=="m" && x=="inch")
    {
        result=data/0.0254;
    }
    else if(val=="m" && x=="feet")
    {
        result=data/0.3048;
    }
    else if(val=="m" && x=="yard")
    {
        result=data/1.0936;
    }
    else if(val=="cm" && x=="m")
    {
        result=data/100.0;
    }
    else if(val=="cm" && x=="mm")
    {
       result=data*10;
    }
    else if(val=="cm" && x=="feet")
    {
       double subresult=data/100.0;
       result=subresult/0.3048;
    }
    else if(val=="cm" && x=="yard")
    {
        double subresult=data/100.0;
        result=subresult/1.0936;
    }
    else if(val=="cm" && x=="inch")
    {
        double subresult=data/100.0;
        result=subresult/0.0254;
    }
    else if(val=="mm" && x=="m")
    {
        result=data/1000.0;
    }
    else if(val=="mm" && x=="cm")
    {
       result=data/10.0;
    }
    else if(val=="mm" && x=="inch")
    {
       double subresult=data/1000.0;
       result=subresult/0.0254;
    }
    else if(val=="mm" && x=="feet")
    {
        double subresult=data/1000.0;
        result=subresult/0.3048;
    }
    else if(val=="mm" && x=="yard")
    {
        double subresult=data/1000.0;
        result=subresult/1.0936;
    }
    else if(val=="inch" && x=="m")
    {
        result=data*0.0254;
    }
    else if(val=="inch" && x=="cm")
    {
      double subresult=data*0.0254;
      result=subresult*100.0;
    }
    else if(val=="inch" && x=="mm")
    {
        double subresult=data*0.0254;
        result=subresult*1000.0;
    }
    else if(val=="inch" && x=="feet")
    {
        double subresult=data*0.0254;
        result=subresult*0.3048;
    }
    else if(val=="inch" && x=="yard")
    {
        double subresult=data*0.0254;
        result=subresult*1.0936;
    }
    else if(val=="feet" && x=="m")
    {
       result=0.3048*data;
    }
    else if(val=="feet" && x=="cm")
    {
       double sub=0.3048*data;
       result=sub*100.0;
    }
    else if(val=="feet" && x=="mm")
    {
       double sub=0.3048*data;
       result=sub*100.0;
    }
    else if(val=="feet" && x=="inch")
    {
       double sub=0.3048*data;
       result=sub*0.0254;
    }
    else if(val=="feet" && x=="yard")
    {
        double sub=0.3048*data;
        result=sub*1.0936;
    }
    else if(val=="yard" && x=="m")
    {
      result=data*1.0936;
    }
    else if(val=="yard" && x=="cm")
    {
      double sub=data*1.0936;
      result=sub*100.0;
    }
    else if(val=="yard" && x=="mm")
    {
        double sub=data*1.0936;
        result=sub*1000.0;
    }
    else if(val=="yard" && x=="feet")
    {
        double sub=data*1.0936;
        result=sub*0.3048;
    }
    else if(val=="yard" && x=="inch")
    {
        double sub=data*1.0936;
        result=sub*0.0254;
    }
    to->setText("Result:"+QString::number(result,'f',3)+" "+tbx->currentText());
}

void MainWindow::menuslot(QAction *a)
{
   if(a->text()=="ABOUT")
   {
       QFile ab(":/about.txt");
       ab.open(QIODevice::ReadOnly);
       QTextStream st(&ab);
       QString msg="<h3>App Copyrights index</h3>!!!<br>";
       while(!st.atEnd())
       {
          msg+=st.readLine()+"<br>";
       }
       ab.close();
       QMessageBox::information(this,"COPYRIGHTS",msg);
   }
   else if(a->text()=="HELP")
   {
       QFile hp(":/help.txt");
       hp.open(QIODevice::ReadOnly);
       QTextStream st(&hp);
       QString msg="<h3 style=text-align:center>App help index!!!</h3><br>";
       msg+="<br>";
       QString date=__DATE__;
       QString time=__TIME__;
       msg+="Viewed at:"+date+"  "+time+"<br>";
       msg+="\n";
       while(!st.atEnd())
       {
          msg+=st.readLine()+"<br>";
       }
       QMessageBox::information(this,"Help",msg);
   }
}

void MainWindow::colorslot(QAction *ac)
{
    if(ac->text()=="LavenderBlush")
    {
       this->centralWidget()->setStyleSheet("background-color:#FFF0F5;");
    }
    else if(ac->text()=="LightSalmon")
    {
      this->centralWidget()->setStyleSheet("background-color:#FFA07A;");
    }
    else if(ac->text()=="MediumOrchid")
    {
      this->centralWidget()->setStyleSheet("background-color:#BA55D3;");
    }
}
