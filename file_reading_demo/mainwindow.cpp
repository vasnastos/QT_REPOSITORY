#include "mainwindow.h"
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,600);
    this->setWindowTitle("File Reader");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lb=new QLabel;
    lb->setFixedSize(0.95*width(),0.3*height());
    QMovie *m=new QMovie;
    m->setFileName(":/pop.gif");
    lb->setMovie(m);
    ml->addWidget(lb);
    lb->movie()->start();
    QPushButton *load=new QPushButton("LOAD");
    load->setStyleSheet("padding: 2px 5px;"
                        "font-size: 19px;"
                        "text-align: center;"
                        "color: #b30046;"
                        "background-color: #e6ffff;"
                        "border: 1px solid black;"
                        "border-radius: 2px solid black;"
                        "font-weight: bold;");
    load->setFixedWidth(0.4*width());
    box=new QComboBox;
    box->setStyleSheet("border: 1px solid gray;"
                       "border-radius: 3px;"
                       "padding: 1px 18px 1px 3px;"
                       "min-width: 6em;");
    QHBoxLayout *r=new QHBoxLayout;
    ml->addLayout(r);
    r->addWidget(load);
    r->addWidget(box);
    connect(load,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(box,SIGNAL(activated(QString)),this,SLOT(comboslot(QString)));
    chart=new QChart;
    series=new QPieSeries;
    chart->addSeries(series);
    view=new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("border:2px solid;"
                        "border-color:red;");
    view->setAlignment(Qt::AlignCenter);
    ml->addWidget(view);
}

MainWindow::~MainWindow() {}

QStringList MainWindow::get_ages()
{
    QStringList l;
    for(auto &x:pop)
    {
        bool found=false;
        for(auto &y:l)
        {
            if(y==x.age)
            {
                found=true;
                break;
            }
        }
        if(!found)
        {
            l<<x.age;
        }
    }
    return l;
}

void MainWindow::loadslot()
{
   QString fn=QFileDialog::getOpenFileName(this,"Open data",".","csv files (*.csv)");
   if(fn.size()==0)
   {
       return;
   }
   QFile fp(fn);
   fp.open(QIODevice::ReadOnly);
   QTextStream st(&fp);
   while(!st.atEnd())
   {
       QString line=st.readLine();
       if(line.startsWith("#")) continue;
       if(line.size()==0) continue;
       QStringList data=line.split(",");
       popul p;
       p.period=data[0];
       p.status=data[1];
       p.gender=data[2];
       p.age=data[3];
       p.count=data[4].toLongLong();
       pop<<p;
   }
   fp.close();
   box->addItems(this->get_ages());
}

void MainWindow::comboslot(QString key)
{
    series->clear();
    chart->removeSeries(series);
  QString s=__TIME__;
  QStringList l=s.split(":");
  int seed=l[l.size()-1].toInt();
  std::mt19937 mt(seed);
  std::uniform_int_distribution <int> dist(0,255);
  int r,g,b;
  for(auto &x:pop)
  {
      if(x.age==key)
      {
          r=dist(mt);
          g=dist(mt);
          b=dist(mt);
        QColor c1;
        c1.setRgb(r,g,b);
        QPieSlice *slice=new QPieSlice(x.period,x.count);
        slice->setLabel(x.period);
        slice->setBrush(c1);
        series->append(slice);
      }
  }
  chart->addSeries(series);
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key()==Qt::Key_S)
    {
        QString fn=QFileDialog::getSaveFileName(this,"Save Screenshot",".","image (*.png)");
        if(fn.size()!=0)
        {
            view->grab().save(fn);
        }
    }
}
