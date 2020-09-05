#include "mainwindow.h"
#include <random>
#include <QMovie>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDesktopWidget wd;
    const int widthdesc=wd.width()/2;
    const int heightdesc=wd.height()/1.5;
    this->setFixedSize(widthdesc,heightdesc);
    this->setWindowTitle("Operating systems usage in Greece");
    this->setWindowIcon(QIcon(":/gr.jpg"));
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    lay=new QVBoxLayout;
    mw->setLayout(lay);
    QLabel *label=new QLabel;
    label->setFixedSize(0.98*this->width(),0.3*this->height());
   QMovie *movie=new QMovie(":/OS.gif");
   QSize sz(label->width(),label->height());
   movie->setScaledSize(sz);
   label->setMovie(movie);
   label->movie()->start();
   lay->addWidget(label);
   QPushButton *but=new QPushButton("Load");
   but->setStyleSheet("background-color:#A9A9A9;"
                      "color:#8B0000;"
                      "font-size:24px;"
                      "padding:2px 5px");
   QPushButton *b=new QPushButton("Export");
   b->setStyleSheet("background-color:#A9A9A9;"
                         "color:#8B0000;"
                         "font-size:24px;"
                         "padding:2px 5px");
   QPushButton *bt=new QPushButton("Data");
   bt->setStyleSheet("background-color:#A9A9A9;"
                     "color:#8B0000;"
                     "font-size:24px;"
                     "padding:2px 5px");
   but->setFixedWidth(0.3*this->width());
   b->setFixedWidth(0.3*this->width());
   bt->setFixedWidth(0.3*this->width());
   QLabel *lb=new QLabel;
   lb->setStyleSheet("background-color:#A9A9A9;"
                     "color:#8B0000;"
                     "font-size:24px;"
                     "border:1px solid;"
                     "border-color:#DC143C;");
   lb->setFixedSize(0.3*this->width(),0.05*this->height());
   lb->setAlignment(Qt::AlignCenter);
   lb->setText("DATA FORM");
   QHBoxLayout *row1=new QHBoxLayout;
   lay->addLayout(row1);
   row1->addWidget(lb);
   row1->addWidget(but);
   row1->addWidget(bt);
   QHBoxLayout *row2=new QHBoxLayout;
   lay->addLayout(row2);
   QLabel *lb1=new QLabel;
   lb1->setStyleSheet("background-color:#A9A9A9;"
                      "color:#8B0000;"
                      "font-size:24px;"
                      "border:1px solid;"
                      "border-color:#DC143C;");
   lb1->setFixedSize(0.3*this->width(),0.05*this->height());
   lb1->setAlignment(Qt::AlignCenter);
   lb1->setText("CHART FORM");
   dates=new QComboBox;
   dates->setFixedWidth(0.3*this->width());
   row2->addWidget(lb1);
   row2->addWidget(dates);
   row2->addWidget(b);
   connect(but,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
   connect(bt,SIGNAL(clicked(bool)),this,SLOT(showdata()));
   connect(b,SIGNAL(clicked(bool)),this,SLOT(exportslot()));
   chart=new QChart();
   series=new QPieSeries;
   chart->addSeries(series);
   vw=new QChartView(chart);
   vw->setRenderHint(QPainter::Antialiasing);
   vw->setFixedSize(0.98*this->width(),0.3*this->height());
   vw->setStyleSheet("border:2px solid;"
                     "border-color:#483D8B;");
   lay->addWidget(vw);
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"Select file",".","(*.csv)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"Error","No file selected");
        return;
    }
    recs.clear();
    dates->clear();
    QFile fp(fn);
    fp.open(QIODevice::ReadOnly);
    QTextStream st(&fp);
    int counter=0;
    while(!st.atEnd())
    {
        QString line=st.readLine();
        if(line.startsWith("#")) continue;
        counter++;
        if(counter==1)
        {
            os=line.split(",");
            os.removeAt(0);
            continue;
        }
        QStringList data=line.split(",");
        opsys record;
        record.Date=data[0];
        for(auto itr=data.begin()+1;itr!=data.end();itr++)
        {
            record.percents.append(itr->toDouble());
        }
        recs.append(record);
    }
    dates->addItems(fillcombo());
    fp.close();
}

void MainWindow::showdata()
{
    QString message="";
    for(auto &x:recs)
    {
        message+="<h3 style=color:#8B0000;>"+x.Date+"</h3>";
        message+="<ul>";
        for(int i=0;i<x.percents.size();i++)
        {
           message+="<li>"+os.at(i)+"--"+QString::number(x.percents.at(i))+"%</li>";
        }
        message+="</ul>";
        message+="\n";
    }
    QMessageBox::information(this,"Show Info",message);
    int quest=QMessageBox::information(this,"Save","Save to file?",QMessageBox::Yes,QMessageBox::No);
    if(quest==QMessageBox::Yes)
    {
        QFile sv(qApp->applicationDirPath()+QDir::separator()+"data.html");
        sv.open(QIODevice::WriteOnly);
        QTextStream tx(&sv);
        tx<<"<h1 style=color:#2F4F4F;>OS USAGE IN GREECE LIST VIEW</h1>";
        tx<<message;
        sv.close();
    }
}

QStringList MainWindow::fillcombo()
{
    QStringList dats;
  for(auto &x:recs)
  {
      bool found=false;
      for(auto &y:dats)
      {
          if(x.Date==y)
          {
              found=true;
              break;
          }
      }
      if(!found)
      {
          dats<<x.Date;
      }
  }
  return dats;
}

void MainWindow::exportslot()
{
    series->clear();
    chart->removeSeries(series);
    QString text=dates->currentText();
    int i=0;
    for(auto &x:recs)
    {
       if(x.Date==text)
       {
           break;
       }
       i++;
    }
    int j=0;
    std::mt19937 mt(1256);
    std::uniform_int_distribution <int> dist(0,255);
    for(auto &y:recs[i].percents)
    {
        QPieSlice *slice=new QPieSlice(os.at(j),y);
        QColor c1;
        c1.setRgb(dist(mt),dist(mt),dist(mt));
        slice->setBrush(c1);
        slice->hovered(true);
        QString spl=os.at(j)+"-"+QString::number(y);
        slice->setProperty("slice",spl);
        connect(slice,SIGNAL(pressed()),this,SLOT(pressedslice()));
        series->append(slice);
        j++;
    }
    chart->addSeries(series);
}

void MainWindow::pressedslice()
{
    QPieSlice *sl=(QPieSlice *)sender();
    QString text=sl->property("slice").toString();
    QStringList data=text.split("-");
    QMessageBox::information(this,"Slice Info","<h2 style=color:#DC143C;>"+data[0]+"</h2>----<b>"+data[1]+"%</b>");
}
