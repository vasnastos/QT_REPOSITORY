#include "mainwindow.h"

QStringList get_distinct_years(QVector <divorce> &ds)
{
    QStringList yrs;
    for(auto &x:ds)
    {
        bool found=false;
        for(auto &y:yrs)
        {
            if(x.year==y.toInt())
            {
                found=true;
                break;
            }
        }
        if(!found)
        {
            yrs.append(QString::number(x.year));
        }
    }
    return yrs;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,600);
    QIcon ic(":/dev.png");
    this->setWindowIcon(ic);
    this->setWindowTitle("Divorce stats");
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *label=new QLabel;
    label->setFixedWidth(0.95*width());
    label->setFixedHeight(0.3 * height());
    QPixmap pix(":/window.png");
    label->setPixmap(pix.scaled(label->width(),label->height()));
    label->setStyleSheet("border:2px dashed;");
    ml->addWidget(label);
    QPushButton *b1=new QPushButton;
    b1->setText("LOAD");
    QPushButton *b2=new QPushButton;
    b2->setText("SAVE");
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(saveslot()));
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    r1->addWidget(b1);
    r1->addWidget(b2);
    tab=new QTableWidget;
    tab->setFixedSize(0.95 * width(),0.3 * height());
    QStringList header;
    header<<"Year"<<"SHOW STATS"<<"SHOW GRAPH"<<"EXPORT";
    tab->setColumnCount(header.size());
    tab->setHorizontalHeaderLabels(header);
    ml->addWidget(tab);
    chart=new QChart;
    srs=new QPieSeries;
    chart->addSeries(srs);
    vw=new QChartView(chart);
    vw->setRenderHint(QPainter::Antialiasing);
    vw->setStyleSheet("border:2px dashed;");
    ml->addWidget(vw);
}

MainWindow::~MainWindow() {}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"Open file",".","csv files (*.csv)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No file selected");
        return;
    }
    QFile fp(fn);
    bool ok=fp.open(QIODevice::ReadOnly);
    if(!ok) return;
    QTextStream st(&fp);
    while(!st.atEnd())
    {
        QString line=st.readLine();
        if(line.startsWith("#")) continue;
        if(line.size()==0) continue;
        QStringList data=line.split(",");
        if(data.size()!=4) continue;
        divorce d;
        d.year=data[0].toInt();
        d.gender=data[1];
        d.avegage=data[2].toDouble();
        d.precent=data[3].toDouble();
        devs<<d;
    }
    fp.close();
    QStringList yrs=get_distinct_years(devs);
    tab->setRowCount(yrs.size());
    tab->setGridStyle(Qt::PenStyle::MPenStyle);
    for(int i=0;i<tab->rowCount();i++)
    {

       tab->setItem(i,0,new QTableWidgetItem(yrs[i]));
       QPushButton *bac1=new QPushButton;
       bac1->setText("SHOW STATS");
       bac1->setProperty("year",yrs[i]);
       tab->setCellWidget(i,1,bac1);
       connect(bac1,SIGNAL(clicked(bool)),this,SLOT(showstats()));
       QPushButton *bac2=new QPushButton;
       bac2->setText("SHOW GRAPH");
       bac2->setProperty("graph",yrs[i]);
       tab->setCellWidget(i,2,bac2);
       connect(bac2,SIGNAL(clicked(bool)),this,SLOT(showgraph()));
       QPushButton *bac3=new QPushButton;
       bac3->setText("EXPORT GRAPH");
       bac3->setProperty("exp",yrs[i]);
       tab->setCellWidget(i,3,bac3);
       connect(bac3,SIGNAL(clicked(bool)),this,SLOT(exportimage()));
    }
}

void MainWindow::saveslot()
{
    QString fn=QFileDialog::getSaveFileName(this,"Save file",".","wordpad files (*.out)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No file selected");
        return;
    }
    QFile fp(fn);
    fp.open(QIODevice::WriteOnly);
    QTextStream st(&fp);
    st<<"File created at:"<<__DATE__<<"---"<<__TIME__<<endl;
    st<<"Fixed stats by years"<<endl;
    QStringList y=get_distinct_years(devs);
    double pm,pfm,other;
    for(auto &x:y)
    {
        st<<"****** Year:"<<x<<" ******"<<endl;
        for(auto &k:devs)
        {
            if(k.year==x.toInt())
            {
                st<<k.gender<<"--"<<"Average Age:"<<k.avegage<<"--Precent:"<<k.precent<<endl;
                if(k.gender=="Male")
                {
                    pm=k.precent;
                }
                if(k.gender=="Female")
                {
                    pfm=k.precent;
                }
            }
        }
        other=100.0-(pm+pfm);
        st<<"Other---Precent:"<<other<<endl;
        st<<"***********************"<<endl;
        st<<endl;
    }
    fp.close();
}

void MainWindow::showstats()
{
   QPushButton *b=(QPushButton *)sender();
   int src=b->property("year").toInt();
   QString k="<html>";
   k+="**** "+QString::number(src)+" ****";
   k+="<ul>";
   for(auto &x:devs)
   {
       if(x.year==src)
       {
         k+="<li>Gender:"+x.gender+"\tAverage:"+QString::number(x.avegage)+"\tPrecent:"+QString::number(x.precent)+"</li>";
       }
   }
   k+="</ul>";
   k+="</html>";
   QMessageBox::information(this,"Info for year:"+QString::number(src),k);
}

void MainWindow::showgraph()
{
    srs->clear();
    QPushButton *b=(QPushButton *)sender();
    double pm,pfm;
    int yr=b->property("graph").toInt();
    for(auto &x:devs)
    {
        if(x.year==yr)
        {
           srs->append(x.gender,x.precent);
           if(x.gender=="Male")
           {
               pm=x.precent;
           }
           if(x.gender=="Female")
           {
               pfm=x.precent;
           }
        }
    }
    double oth=100.0-(pm+pfm);
    srs->append("Other",oth);
    chart->setTitle("Information for year "+QString::number(yr));
    chart->removeSeries(srs);
    chart->addSeries(srs);
}

void MainWindow::exportimage()
{
    srs->clear();
    QPushButton *b=(QPushButton *)sender();
    double pm,pfm;
    int yr=b->property("exp").toInt();
    for(auto &x:devs)
    {
        if(x.year==yr)
        {
           srs->append(x.gender,x.precent);
           if(x.gender=="Male")
           {
               pm=x.precent;
           }
           if(x.gender=="Female")
           {
               pfm=x.precent;
           }
        }
    }
    double oth=100.0-(pm+pfm);
    srs->append("Other",oth);
    chart->setTitle("Information for year "+QString::number(yr));
    chart->removeSeries(srs);
    chart->addSeries(srs);
    QPixmap pix=vw->grab();
    QString fn=QFileDialog::getSaveFileName(this,"Save Image",".","png files (*.png)");
    if(fn.size()!=0)
    {
        pix.save(fn,"png");
    }
}
