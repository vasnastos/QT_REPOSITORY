#include "mainwindow.h"

QStringList get_distinct_years(QVector <abortion> &abs)
{
    QStringList years;
    bool found;
    for(auto &x:abs)
    {
        found=false;
        for(auto &y:years)
        {
          if(x.year==y.toInt())
          {
              found=true;
              break;
          }
        }
        if(!found)
        {
            years.append(QString::number(x.year));
        }
    }
    return years;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(1000,1000);
    QIcon icon1(":/wstats.png");
    this->setWindowIcon(icon1);
    this->setWindowTitle("Abortion rate");
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *desc=new QLabel;
    QPixmap pix1(":/central.jpg");
    desc->setFixedWidth(0.96*width());
    desc->setFixedHeight(0.3 * height());
    desc->setPixmap(pix1.scaled(desc->width(),desc->height()));
    desc->setStyleSheet("border:2px;");
    ml->addWidget(desc);
    make_menu();
    QLabel *in=new QLabel;
    in->setText("<h2 style=text-align:center; font-family:calibri;>RECORD YEARS</h2>");
    in->setStyleSheet("background-color:red;");
    QHBoxLayout *r2=new QHBoxLayout;
    combo=new QComboBox;
    ml->addLayout(r2);
    r2->addWidget(in);
    r2->addWidget(combo);
    QPushButton *b1=new QPushButton;
    b1->setText("SEARCH RATES");
    QPushButton *b2=new QPushButton;
    b2->setText("STATS PER YEAR");
    QPushButton *b3=new QPushButton;
    b3->setText("AVERAGE RATE");
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    r1->addWidget(b1);
    r1->addWidget(b2);
    r1->addWidget(b3);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(rateperyearslot()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(Statsperyear()));
    connect(b3,SIGNAL(clicked(bool)),this,SLOT(avgrateslot()));
    tab=new QTableWidget;
    QStringList data;
    data<<"PERIOD"<<"AGE OF WOMEN"<<"ABORTION RATE";
    tab->setColumnCount(data.size());
    tab->setHorizontalHeaderLabels(data);
    tab->setFixedWidth(0.96 * width());
    tab->setFixedHeight(0.2 * height());
    ml->addWidget(tab);
    chart=new QChart();
    chart->setTitle("<p style=color:red>ABORTION RATE</p>");
    series=new QPieSeries;
    chart->addSeries(series);
    slice=new QPieSlice;
    series->append(slice);
    view=new QChartView(chart);
    view->setRenderHint(QPainter::Antialiasing);
    view->grabShortcut('z');
    ml->addWidget(view);
}

void MainWindow::make_menu()
{
   QMenu *fm=new QMenu("FILE");
   //QMenu *ed=new QMenu("")
   QIcon icon2(":/load.png");
   fm->addAction(icon2,"LOAD");
   QIcon icon3(":/save.png");
   fm->addAction(icon3,"SAVE");
   QIcon iconnew(":/export.png");
   fm->addAction(iconnew,"EXPORT");
   QIcon icon4(":/quit.png");
   fm->addAction(icon4,"QUIT");
   menuBar()->addMenu(fm);
   connect(fm,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
}

void MainWindow::menuslot(QAction *a)
{
    if(a->text()=="LOAD")
    {
        QString fn=QFileDialog::getOpenFileName(this,"Open data",".","txt files (*.txt *.csv)");
       if(fn.size()==0)
       {
          QMessageBox::critical(this,"ERROR","No file selected");
          return;
       }
       QFile fp(fn);
       bool ok=fp.open(QIODevice::ReadOnly | QIODevice::Text);
       if(!ok) return;
       QTextStream st(&fp);
       while(!st.atEnd())
       {
         QString line=st.readLine();
         if(line.startsWith("#")) continue;
        if(line.size()==0) continue;
        QStringList data=line.split(",");
        if(data.size()!=3) continue;
        abortion ab;
        ab.year=data[0].toInt();
        ab.age=data[1];
        ab.rate=data[2].toDouble();
        abortinfo.append(ab);
        emit tableview();
       }
       fp.close();
       combo->addItems(get_distinct_years(abortinfo));
    }
    else if(a->text()=="SAVE")
    {
        QString fn=QFileDialog::getSaveFileName(this,"save file",".","csv file (*.csv)");
        if(fn.size()==0)
        {
           QMessageBox::critical(this,"ERROR","No file selected");
           return;
        }
        if(abortinfo.size()==0)
        {
            QMessageBox::critical(this,"Error","No valid information have been loaded to the program");
            return;
        }
        QFile fp(fn);
        fp.open(QIODevice::WriteOnly);
        QTextStream st(&fp);
        st<<"PERIOD"<<" AGE OF WOMEN"<<" ABORTION RATE"<<endl;
        for(auto &x:abortinfo)
        {
            st<<x.year<<" "<<x.age<<" "<<x.rate<<endl;
        }
        fp.close();
    }
    else if(a->text()=="EXPORT")
    {
       QString filename=QFileDialog::getSaveFileName(this,"save chart",".","png files (*.png)");
       if(filename.size()!=0)
       {
           QPixmap pix=view->grab();
           pix.save(filename,"png");
       }
    }
    else if(a->text()=="QUIT")
    {
        qApp->exit(EXIT_SUCCESS);
    }
}

MainWindow::~MainWindow() {}

void MainWindow::rateperyearslot()
{
    if(abortinfo.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No valid records load");
        return;
    }
    int syear=combo->currentText().toInt();
    QString info="INFO FOR YEAR "+QString::number(syear)+"<ul>\n";
    for(auto &x:abortinfo)
    {
        if(x.year==syear)
        {
           info+="<li>AGES:"+x.age+"\tRATE:"+QString::number(x.rate)+"</li>";
        }
    }
    info+="</ul>";
    QMessageBox::information(this,"INFO FOR YEAR "+QString::number(syear),info);
}

void MainWindow::avgrateslot()
{
    if(abortinfo.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No valid records load");
        return;
    }
    int syear=combo->currentText().toInt();
    double sum=0.0;
    int counter=0;
    for(auto &x:abortinfo)
    {
        if(x.year==syear)
        {
            sum+=x.rate;
            counter++;
        }
    }
    QMessageBox::information(this,"INFO FOR YEAR "+QString::number(syear),"Average rate:"+QString::number(sum/counter));
}

void MainWindow::Statsperyear()
{
    if(abortinfo.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No valid records load");
        return;
    }
    series->clear();
    int syear=combo->currentText().toInt();
    chart->setTitle("<h2>Abortion Rate for year "+QString::number(syear)+"</h2>");
    for(auto &x:abortinfo)
    {
        if(x.year==syear)
        {
            series->append(x.age,x.rate);
        }
    }
    chart->removeSeries(series);
    chart->addSeries(series);
}

void MainWindow::tableview()
{
    tab->clearContents();
    tab->setRowCount(abortinfo.size());
    for(int i=0;i<tab->rowCount();i++)
    {
        tab->setItem(i,0,new QTableWidgetItem(QString::number(abortinfo[i].year)));
        tab->setItem(i,1,new QTableWidgetItem(abortinfo[i].age));
        tab->setItem(i,2,new QTableWidgetItem(QString::number(abortinfo[i].rate)));
    }
}
