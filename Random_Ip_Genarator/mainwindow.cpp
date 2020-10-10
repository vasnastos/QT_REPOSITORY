#include "mainwindow.h"
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(400,650);
    this->setWindowTitle("Random Ip Genarator");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    ml->setSpacing(2);
    QLabel *gif=new QLabel;
    gif->setFixedSize(0.98*width(),0.3*height());
    QMovie *movie=new QMovie;
    movie->setFileName(":/ip.gif");
    QSize sz(gif->width(),gif->height());
    movie->setScaledSize(sz);
    gif->setMovie(movie);
    ml->addWidget(gif);
    gif->movie()->start();
    num=new QLineEdit;
    num->setFixedWidth(0.2*this->width());
    num->setStyleSheet("color:#660033;"
                       "background-color:#f2f2f2;"
                       "border:2px solid;");
    num->setText("0");
    QPushButton *b=new QPushButton;
    b->setStyleSheet("background-color:#f2f2f2;"
                     "color:#660033;"
                     "padding:2px 5px");
    b->setFixedWidth(0.2*this->width());
    b->setText("GENARATE");
    QHBoxLayout *bx=new QHBoxLayout;
    ml->addLayout(bx);
    bx->addWidget(num);
    bx->addWidget(b);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(genarate()));
    showlb=new QTextEdit;
    showlb->setFixedSize(0.95*width(),0.22*height());
    showlb->setAlignment(Qt::AlignCenter);
    showlb->setStyleSheet("color:#660033;"
                          "border:2px solid;"
                          "font-size:21px;");
    ml->addWidget(showlb);
    chart=new QChart;
    chart->setTitle("Classes Info");
    series=new QPieSeries;
    chart->addSeries(series);
    view=new QChartView(chart);
    view->setStyleSheet("border:2px solid;");
    view->setFixedSize(0.98*this->width(),0.23*this->height());
    ml->addWidget(view);
    make_menu();
}

void MainWindow::make_menu()
{
    QMenu *menu=new QMenu("EDIT");
    menu->addAction(QIcon(":/clear.png"),"CLEAR");
    menu->addAction(QIcon(":/csv.png"),"EXPORT CSV");
    menu->addAction(QIcon(":/export.png"),"EXPORT");
    menu->addAction(QIcon(":/quit.png"),"QUIT");
    menuBar()->addMenu(menu);
    connect(menu,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::menuslot(QAction *a)
{
   if(a->text()=="CLEAR")
   {
     showlb->clear();
     ips.clear();
   }
   else if(a->text()=="EXPORT")
   {
       QString fn=QFileDialog::getSaveFileName(this,"Save Image",".","(images) (*.png *.jpg)");
       view->grab().save(fn);
   }
   else if(a->text()=="EXPORT CSV")
   {
       QString fn=QFileDialog::getSaveFileName(this,"Save ips",".","(csv files) (*.csv)");
       if(fn.size()==0)
       {
           QMessageBox::critical(this,"Error","No input file detected");
           return;
       }
       if(ips.size()==0) {QMessageBox::critical(this,"Error","No input Ips Detected"); return;}
       QFile fp(fn);
       fp.open(QIODevice::WriteOnly);
       QTextStream st(&fp);
       for(auto &x:ips)
       {
           st<<x<<endl;
       }
       fp.close();
   }
   else
   {
      qApp->exit(EXIT_SUCCESS);
   }
}

int seed()
{
    QString time=__TIME__;
    QStringList list=time.split(":");
    return list[list.size()-1].toInt();
}

void MainWindow::genarate()
{
    ips.clear();
   std::mt19937 mt(seed());
   int size=num->text().toInt();
   std::uniform_int_distribution <int> numbers(0,255);
   for(int i=0;i<size;i++)
   {
      QString x="";
      for(int j=0;j<3;j++)
      x+=QString::number(numbers(mt))+".";
      x+=QString::number(numbers(mt));
      ips.append(x);
   }
   QString message="<h3 text-align:center;>Randoms Ip</h3><ul>";
   for(auto &x:ips)
   {
      message+="<li>"+x+"</li>";
   }
   message+="</ul>";
   showlb->setText(message);
   series->clear();
   chart->removeSeries(series);
   int cntA=0;
   int cntB=0;
   int cntC=0;
   int cntD=0;
   int cntE=0;
   for(int i=0;i<ips.size();i++)
   {
      QStringList data=ips[i].split(".");
      int firstdigit=data[0].toInt();
      if(firstdigit>=0 && firstdigit<=121)
      {
          cntA++;
      }
      else if(firstdigit<=191)
      {
          cntB++;
      }
      else if(firstdigit<=223)
      {
          cntC++;
      }
      else if(firstdigit<=240)
      {
          cntD++;
      }
      else if(firstdigit<=255)
      {
          cntE++;
      }
   }
   for(int k=0;k<5;k++)
   {
       QPieSlice *sl1;
       QString limit;
       if(k==0)
       {
           sl1=new QPieSlice("Class A",(double)cntA/ips.size());
           limit="0-121";
       }
       else if(k==1)
       {
           sl1=new QPieSlice("Class A",(double)cntB/ips.size());
           limit="122-191";
       }
       else if(k==2)
       {
           sl1=new QPieSlice("Class A",(double)cntC/ips.size());
           limit="192-223";
       }
       else if(k==3)
       {
           sl1=new QPieSlice("Class A",(double)cntD/ips.size());
           limit="224-239";
       }
       else
       {
           sl1=new QPieSlice("Class A",(double)cntE/ips.size());
           limit="240-255";
       }
       QColor c1;
       c1.setRgb(numbers(mt),numbers(mt),numbers(mt));
       sl1->setBrush(c1);
       sl1->setProperty("Class",limit);
       series->append(sl1);
       connect(sl1,SIGNAL(pressed()),this,SLOT(showipslot()));
   }
   chart->addSeries(series);
}

void MainWindow::showipslot()
{
    QPieSlice *pressedslice=(QPieSlice *)sender();
    QString limit=pressedslice->property("Class").toString();
    QStringList data=limit.split("-");
    int lowerbound=data[0].toInt();
    int upperbound=data[1].toInt();
    QString message="<h2 text-align:center>Ips in this Class</h2><ul>";
    for(auto &x:ips)
    {
        QStringList data=x.split(".");
        int firstdigit=data[0].toInt();
        if(firstdigit>=lowerbound && firstdigit<=upperbound)
        {
          message+="<li>"+x+"</li>";
        }
    }
    message+="</ul>";
    QMessageBox::information(this,"Slice Information",message);
}
