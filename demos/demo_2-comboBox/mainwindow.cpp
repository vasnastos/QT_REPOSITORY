#include "mainwindow.h"

QStringList get_distinct_periods(QVector <population> &popls)
{
    QStringList lst;
    for(auto &x:popls)
    {
        bool found=false;
        for(auto &y:lst)
        {
            if(x.period==y)
            {
                found=true;
            }
        }
        if(!found)
        {
            lst<<x.period;
        }
    }
    return lst;
}

QStringList get_distinct_ages(QVector <population> &popls)
{
    QStringList lst;
    for(auto &x:popls)
    {
        bool found=false;
        for(auto &y:lst)
        {
            if(x.age==y)
            {
                found=true;
            }
        }
        if(!found)
        {
            lst<<x.age;
        }
    }
    return lst;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800,600);
    this->setWindowTitle("Population file handling");
    QIcon ic(":/win.png");
    this->setWindowIcon(ic);
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lb=new QLabel;
    lb->setFixedSize(0.95*width(),0.35 * height());
    QPixmap pix(":/central.png");
    lb->setPixmap(pix.scaled(lb->width(),lb->height()));
    lb->setStyleSheet("border:2px inset;");
    ml->addWidget(lb);
    QLabel *in=new QLabel;
    in->setText("<p style=color:red>SELECT AGE</p>");
    in->setAlignment(Qt::AlignCenter);
    box=new QComboBox;
    QHBoxLayout *r1=new QHBoxLayout;
    QPushButton *b1=new QPushButton;
    QIcon icon(":/charticon.png");
    b1->setFixedWidth(0.3 * width());
    b1->setIcon(icon);
    ml->addLayout(r1);
    r1->addWidget(in);
    r1->addWidget(box);
    r1->addWidget(b1);
    connect(box,SIGNAL(activated(QString)),this,SLOT(comboage(QString)));
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(showgraph()));
    ch=new QChart();
    ch->setTitle("<p style=color:blue>Age chart</p>");
    series=new QPieSeries;
    ch->addSeries(series);
    view=new QChartView(ch);
    view->setStyleSheet("border:2px inset;");
    view->setFixedHeight(0.5 * height());
    ml->addWidget(view);
    make_menu();
}

MainWindow::~MainWindow() {}

void MainWindow::make_menu()
{
    QMenu *fn=new QMenu("FILE");
    QMenu *ed=new QMenu("EDIT");
    QIcon ic(":/load.png");
    fn->addAction(ic,"LOAD");
    QIcon ic1(":/savechart.png");
    fn->addAction(ic1,"EXPORT");
    QIcon ic2(":/quit.png");
    fn->addAction(ic2,"QUIT");
    QIcon ic3(":/age.png");
    QIcon ic4(":/period.png");
    QIcon ic5(":/save.png");
    ed->addAction(ic3,"Save by age");
    ed->addAction(ic4,"Save by period");
    ed->addAction(ic5,"Save to wordpad");
    menuBar()->addMenu(fn);
    menuBar()->addMenu(ed);
    connect(fn,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
    connect(ed,SIGNAL(triggered(QAction *)),this,SLOT(editslot(QAction *)));
}

void MainWindow::menuslot(QAction *a)
{
    if(a->text()=="LOAD")
    {
        QString fn=QFileDialog::getOpenFileName(this,"Open Data",".","csv files (*.csv)");
        if(fn.size()==0)
        {
            QMessageBox::critical(this,"Error","No file Selected");
            return;
        }
        QFile op(fn);
        bool ok=op.open(QIODevice::ReadOnly);
        if(!ok) return;
        QTextStream st(&op);
        while(!st.atEnd())
        {
            QString line=st.readLine();
            if(line.startsWith("#")) continue;
            if(line.size()==0) continue;
            QStringList data=line.split(",");
            if(data.size()!=5) continue;
            population p;
            p.period=data[0];
            p.status=data[1];
            p.gender=data[2];
            p.age=data[3];
            p.count=data[4].toLongLong();
            pops<<p;
        }
        op.close();
        QStringList items=get_distinct_ages(pops);
        box->addItems(items);
    }
    else if(a->text()=="EXPORT")
    {
        QString fn=QFileDialog::getSaveFileName(this,"Save image",".","png files (*.png)");
        if(fn.size()!=0)
        {
            QPixmap px=view->grab();
            px.save(fn,"png");
        }
    }
    else
    {
        qApp->exit(EXIT_SUCCESS);
    }
}

void MainWindow::editslot(QAction *a)
{
    if(a->text()=="Save by age")
    {
        QString fn=QFileDialog::getSaveFileName(this,"Save file",".","csv file (*.csv)");
        if(fn.size()==0)
        {
            QMessageBox::critical(this,"Error","No file selected");
            return;
        }
        QFile fp(fn);
        fp.open(QIODevice::WriteOnly);
        QTextStream stream(&fp);
        QStringList lst=get_distinct_ages(pops);
        stream<<"          File editing by Qt program for population handling"<<endl;
        stream<<"          At date:"<<__DATE__<<endl;
        stream<<"          At time:"<<__TIME__<<endl;
        for(auto &x:lst)
        {
            stream<<"******** AGE:"<<x<<" **********"<<endl;
            for(auto &y:pops)
            {
                if(y.age==x)
                {
                    stream<<"PERIOD:"<<y.period<<"\tSTATUS:"<<y.status<<"\tGender:"<<y.gender<<"\tPopulation:"<<y.count<<endl;
                }
            }
            stream<<"********************************"<<endl;
            stream<<endl;
        }
        fp.close();
    }
    else if(a->text()=="Save by period")
    {
         QString fn=QFileDialog::getSaveFileName(this,"Save file",".","csv files (*.csv)");
         if(fn.size()==0)
         {
             QMessageBox::critical(this,"Error","No file selected");
             return;
         }
         QFile fp(fn);
         fp.open(QIODevice::WriteOnly);
         QTextStream stream(&fp);
         QStringList lst=get_distinct_periods(pops);
         stream<<"          File editing by Qt program for population handling"<<endl;
         stream<<"          At date:"<<__DATE__<<endl;
         stream<<"          At time:"<<__TIME__<<endl;
         for(auto &x:lst)
         {
             stream<<"******** PERIOD:"<<x<<" **********"<<endl;
             for(auto &y:pops)
             {
                 if(y.age==x)
                 {
                     stream<<"AGE:"<<y.age<<"\tSTATUS:"<<y.status<<"\tGender:"<<y.gender<<"\tPopulation:"<<y.count<<endl;
                 }
             }
             stream<<"********************************"<<endl;
             stream<<endl;
         }
         fp.close();
    }
    else if(a->text()=="Save to wordpad")
    {
        QString fn=QFileDialog::getSaveFileName(this,"Save file",".","wordpad files (*.csv)");
        if(fn.size()==0)
        {
            QMessageBox::critical(this,"Error","No file selected");
            return;
        }
        QFile fp(fn);
        fp.open(QIODevice::WriteOnly);
        QTextStream stream(&fp);
        stream<<"############ Population Records ############"<<endl;
        for(auto &x:pops)
        {
            stream<<"PERIOD:"<<x.period<<"\tSTATUS:"<<x.status<<"\tGender:"<<x.gender<<"\tAge:"<<x.age<<"\tPopulation:"<<x.count<<endl;
        }
        stream<<"#############################################"<<endl;
    }
}

void MainWindow::comboage(QString ag)
{
   QString msg="<html>";
   msg+="<h2 style=text-align:center; colr:red;>AGE "+ag+" information</h2>";
   msg+="</ul>";
   for(auto &x:pops)
   {
       if(x.age==ag)
       {
         msg+="<li>Period:"+x.period+"\tStatus:"+x.status+"\tGender:"+x.gender+"\tCount"+QString::number(x.count)+"</li>";
       }
   }
   msg+="</ul>";
   msg+="</html>";
   QMessageBox::information(this,"Info for age:"+ag,msg);
}

void MainWindow::showgraph()
{
    series->clear();
    QString age=box->currentText();
    ch->setTitle("<b>Graph for age:"+age+"</b>");
    for(auto &x:pops)
    {
        if(x.age==age)
        {
            QString n=x.period+"--"+x.gender;
            series->append(n,x.count);
        }
    }
    ch->removeSeries(series);
    ch->addSeries(series);
}
