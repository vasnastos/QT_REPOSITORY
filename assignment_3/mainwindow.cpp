#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(900,900);
    this->setWindowTitle("FOOTBALL RESULTS");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lb=new QLabel;
    lb->setFixedSize(0.96 * width(),0.30 * height());
    QPixmap pix(":/stadium.png");
    lb->setPixmap(pix.scaled(lb->width(),lb->height()));
    ml->addWidget(lb);
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    QPushButton *l=new QPushButton;
    l->setText("LOAD");
    QPushButton *s=new QPushButton;
    s->setText("SHOW FIXTURES");
    QPushButton *c=new QPushButton;
    c->setText("CLEAR");
    connect(l,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(s,SIGNAL(clicked(bool)),this,SLOT(showslot()));
    connect(c,SIGNAL(clicked(bool)),this,SLOT(clearslot()));
    r1->addWidget(l);
    r1->addWidget(s);
    r1->addWidget(c);
    series=new QPieSeries;
    chart=new QChart();
    chart->setTitle("Fixtures");
    chart->addSeries(series);
    view=new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    ml->addWidget(view);
}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"file open",".","txt files (*.txt *.csv)");
    if(fn.size()==0) return;
    QFile fp(fn);
    bool ok=fp.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ok) return;
    QTextStream st(&fp);
    while(!st.atEnd())
    {
        QString line=st.readLine();
        if(line.startsWith("#")) continue;
        if(line.size()==0) continue;
        QStringList data=line.split("-");
        if(data.size()!=2) continue;
        int score1=data[0].toInt();
        int score2=data[1].toInt();
        if(score1>score2)
        {
            res<<1;
        }
        else if(score1<score2)
        {
            res<<2;
        }
        else
        {
            res<<0;
        }
    }
    fp.close();
}
MainWindow::~MainWindow() {}

void MainWindow::showslot()
{
    int countwins=0,countslose=0,countstie=0;
    for(int i=0;i<res.size();i++)
    {
       if(res[i]==0) countstie++;
       else if(res[i]==1) countwins++;
       else if(res[i]==2) countslose++;
    }
    series->append("Wins",countwins);
    series->append("Loses",countslose);
    series->append("Ties",countstie);
    chart->removeSeries(series);
    chart->addSeries(series);
}

void MainWindow::clearslot()
{
    res.clear();
    series->clear();
}
