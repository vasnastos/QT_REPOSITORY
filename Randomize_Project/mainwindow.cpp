#include "mainwindow.h"
#include <random>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,600);
    this->setWindowTitle("Randomize Project");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lb=new QLabel;
    lb->setFixedSize(0.98*this->width(),0.3*this->height());
    QMovie *m=new QMovie();
    m->setFileName(":/random.gif");
    QSize s(lb->width(),lb->height());
    m->setScaledSize(s);
    lb->setMovie(m);
    lb->movie()->start();
    ml->addWidget(lb);
    b=new QPushButton("RANDOM");
    b1=new QPushButton("SUMMARY");
    QPushButton *b2=new QPushButton("AVERAGE");
    b1->setStyleSheet("color:#e0385a;"
                      "background-color:#0b05b5;"
                      "text-align:center;"
                      "border:2px solid;"
                      "padding:1px 3px;");
    b->setStyleSheet("color:#e0385a;"
                     "background-color:#0b05b5;"
                     "text-align:center;"
                     "border:2px solid;"
                     "padding:1px 3px;");
    b2->setStyleSheet("color:#e0385a;"
                     "background-color:#0b05b5;"
                     "text-align:center;"
                     "padding:1px 3px;"
                     "border:2px solid;");
   QHBoxLayout *row=new QHBoxLayout;
   ml->addLayout(row);
   row->addWidget(b);
   row->addWidget(b1);
   row->addWidget(b2);
   connect(b,SIGNAL(clicked(bool)),this,SLOT(add_random()));
   connect(b1,SIGNAL(clicked(bool)),this,SLOT(sum()));
   connect(b2,SIGNAL(clicked(bool)),this,SLOT(average()));
   chart=new QChart;
   chart->setTitle("Over average");
   series=new QPieSeries;
   chart->addSeries(series);
   view=new QChartView(chart);
   view->setRenderHint(QPainter::Antialiasing);
   view->setStyleSheet("background-color:;"
                       "border:2px solid;"
                       "border-color:red;");
   view->setFixedSize(0.98*this->width(),0.4*this->height());
   ml->addWidget(view);
   connect(this,SIGNAL(valueadded()),this,SLOT(reinform()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::add_random()
{
  int number=rand()%1000;
  numbers<<number;
  emit reinform();
}

void MainWindow::sum()
{
    int sumv=0;
    for(int i=0;i<numbers.size();i++)
    {
        sumv+=numbers.at(i);
    }
    QMessageBox::information(this,"SUMMARY","<h3 style=color:red>Sum:"+QString::number(sumv)+"</h3>");
}

void MainWindow::average()
{
    int sumv=0;
    for(int i=0;i<numbers.size();i++)
    {
        sumv+=numbers.at(i);
    }
    QMessageBox::information(this,"SUMMARY","<h3 style=color:red>Average:"+QString::number((double)sumv/numbers.size())+"</h3>");
}

void MainWindow::reinform()
{
  double average;
  int sumv=0;
  for(int i=0;i<numbers.size();i++)
  {
      sumv+=numbers.at(i);
  }
  average=(double)sumv/numbers.size();
  chart->removeSeries(series);
  series->clear();
  int up=0,down=0;
  for(auto itr=numbers.begin();itr!=numbers.end();itr++)
  {
      if((double)(*itr)>average)
      {
          up++;
      }
      else
      {
          down++;
      }
  }
  double percentover=((double)up/numbers.size())*100.0;
  double percentdown=((double)down/numbers.size())*100.0;
  QPieSlice *slice1=new QPieSlice("Over",percentover);
  QPieSlice *slice2=new QPieSlice("Under",percentdown);
  slice1->setBrush(Qt::darkGreen);
  slice2->setBrush(Qt::darkRed);
  series->append(slice1);
  series->append(slice2);
  chart->addSeries(series);
}
