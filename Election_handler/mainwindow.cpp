#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(750,750);
    this->setWindowTitle("USA ELECTION 2016 RESULTS");
    this->setWindowIcon(QIcon(":/central.png"));
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    mw->setStyleSheet("background-color:#ffe6cc;");
    this->setCentralWidget(mw);
    ml=new QStackedLayout;
    mw->setLayout(ml);
    make_tab1();
    make_tab2();
    make_menu();
}

void MainWindow::make_tab1()
{
    QWidget *tab1=new QWidget;
    tab1->setFixedSize(width(),height());
    ml->addWidget(tab1);
    QVBoxLayout *lay=new QVBoxLayout;
    tab1->setLayout(lay);
    QLabel *basic=new QLabel;
    basic->setFixedSize(0.95 * width(),0.30 * height());
    QPixmap pix(":/election.png");
    basic->setPixmap(pix.scaled(basic->width(),basic->height()));
    basic->setStyleSheet("border:2px solid;");
    lay->addWidget(basic);
    tab=new QTableWidget;
    QStringList header;
    header<<"State Code"<<"StateName"<<"Show State Countries"<<"Show state stats";
    tab->setColumnCount(header.size());
    tab->setHorizontalHeaderLabels(header);
    tab->setFixedWidth(0.95*width());
    tab->setFixedHeight(0.5 * height());
    for(int i=0;i<tab->columnCount();i++)
    {
        tab->setColumnWidth(i,0.93*tab->width()/tab->columnCount());
    }
    lay->addWidget(tab);
    this->load_content();
    this->get_states();
}

void MainWindow::load_content()
{
   QFile fp(":/source.csv");
   fp.open(QIODevice::ReadOnly);
   QTextStream st(&fp);
   int counter=0;
   while(!st.atEnd())
   {
       counter++;
       QString line=st.readLine();
       QStringList data=line.split(",");
       if(data.size()!=8) continue;
       if(counter==1) continue;
       election newrecord(data[0],data[1],data[2],data[3],data[4].toLongLong(),data[5],data[6],data[7].toLongLong());
       results<<newrecord;
   }
   fp.close();
}

void MainWindow::get_states()
{
   QStringList lst;
   for(auto &kv:results)
   {
       bool found=false;
       for(auto &st:lst)
       {
           QString search=kv.get_state_code()+"-"+kv.get_state_name();
           if(st==search)
           {
               found=true;
                break;
           }

       }
       if(!found)
       {
           lst<<kv.get_state_code()+"-"+kv.get_state_name();
       }
   }
   tab->setRowCount(lst.size());
   for(int i=0;i<tab->rowCount();i++)
   {
       QStringList spl=lst[i].split("-");
       tab->setItem(i,0,new QTableWidgetItem(spl[0]));
       tab->setItem(i,1,new QTableWidgetItem(spl[1]));
       QPushButton *b1=new QPushButton;
       b1->setText("Countries");
       b1->setStyleSheet("padding: 2px 5px;"
                             "font-size: 20px;"
                             "text-align: center;"
                             "color: #fff;"
                             "background-color:#a83236;"
                             "border: none;"
                             "border-radius: 8px;");
       b1->setProperty("state",spl[1]);
       tab->setCellWidget(i,2,b1);
       QPushButton *b2=new QPushButton;
               b2->setText("State Info");
               b2->setStyleSheet("padding: 2px 5px;"
                                     "font-size: 20px;"
                                     "text-align: center;"
                                     "color: #fff;"
                                     "background-color:#a83236;"
                                     "border: none;"
                                     "border-radius: 8px;");
        b2->setProperty("state",spl[1]);
        tab->setCellWidget(i,3,b2);
        connect(b1,SIGNAL(clicked(bool)),this,SLOT(showcountrieslist()));
        connect(b2,SIGNAL(clicked(bool)),this,SLOT(stateinfo()));
   }
}

void MainWindow::make_tab2()
{
    QWidget *tab2=new QWidget;
    tab2->setFixedSize(width(),height());
    tab2->setStyleSheet("background-color:white;");
    ml->addWidget(tab2);
    QVBoxLayout *lay=new QVBoxLayout;
    tab2->setLayout(lay);
    set=new QLabel;
    set->setAlignment(Qt::AlignCenter);
    set->setStyleSheet("background-color:#999933;"
                       "border:2px solid");
    set->setFixedSize(0.95 * width(),0.10*height());
    lay->addWidget(set);
    states=new QTableWidget;
    states->setFixedWidth(0.95*width());
    states->setFixedHeight(0.50*height());
    QStringList header;
    header<<"Country name"<<"show stats";
    states->setColumnCount(header.size());
    states->setHorizontalHeaderLabels(header);
    for(int i=0;i<states->columnCount();i++)
    {
        states->setColumnWidth(i,(0.92*width())/states->columnCount());
    }
    lay->addWidget(states);
    chart=new QChart;
    series=new QPieSeries;
    chart->addSeries(series);
    view=new QChartView(chart);
    view->setStyleSheet("border:2px solid;");
    view->setFixedWidth(0.95*width());
    view->setFixedHeight(0.3 * height());
    lay->addWidget(view);
}

MainWindow::~MainWindow() {}
void MainWindow::make_menu()
{
    QMenu *men=new QMenu("CHOICES");
    men->addAction(QIcon(":/export.png"),"EXPORT");
    men->addAction(QIcon(":/back"),"BACK");
    men->addAction(QIcon(":/save.png"),"SAVE");
    men->addAction(QIcon(":/quit.png"),"QUIT");
    menuBar()->addMenu(men);
    connect(men,SIGNAL(triggered(QAction *)),this,SLOT(mslot(QAction *)));
}
QStringList MainWindow::get_countries_by_state(QString n)
{
    QStringList countries;
    for(auto &x:results)
    {
        bool found=false;
        if(x.get_state_name()==n)
        {
            for(auto &y:countries)
            {
                if(y==x.get_country_name())
                {
                    found=true;break;
                }
            }
            if(!found)
            countries<<x.get_country_name();
        }
    }
    return countries;
}


void MainWindow::showcountrieslist()
{
    QPushButton *b=(QPushButton *)sender();
    QString name=b->property("state").toString();
    QString msg="<html>";
    msg+="<h4 style=color:red>Countries in "+name+"</h4>";
    msg+="<ul>";
    QStringList cities=this->get_countries_by_state(name);
    for(auto &x:cities)
    {
        msg+="<li><b>"+x+"</b></li>";
    }
    msg+="</ul>";
    msg+="</html>";
    QMessageBox::information(this,"Information for state:"+name,msg);
}

void MainWindow::stateinfo()
{
    states->clearContents();
    ml->setCurrentIndex(1);
    QPushButton *send=(QPushButton *)sender();
    QString stname=send->property("state").toString();
    set->setText("<b>Info for state:"+stname+"<b>");
    QStringList cnts=this->get_countries_by_state(stname);
    states->setRowCount(cnts.size());
    for(int i=0;i<states->rowCount();i++)
    {
        states->setItem(i,0,new QTableWidgetItem(cnts[i]));
        QPushButton *b=new QPushButton;
        b->setText("Stats");
        b->setProperty("country",cnts[i]+"-"+stname);
        b->setStyleSheet("padding: 2px 5px;"
                              "font-size: 20px;"
                              "text-align: center;"
                              "color: #fff;"
                              "background-color:#a83236;"
                              "border: none;"
                              "border-radius: 8px;");
        states->setCellWidget(i,1,b);
        connect(b,SIGNAL(clicked(bool)),this,SLOT(showgraph()));
    }
}

QString MainWindow::file_saving_mode()
{
    QString text="";
    QString datatime=__TIME__;
    QString datadate=__DATE__;
    text+="*********** File syntax completed at:"+datatime+"   "+datatime+"***********\n";
    text+="\n";
    text+="********************************************************************************";
    QStringList lst;
    for(auto &kv:results)
    {
        bool found=false;
        for(auto &st:lst)
        {
            if(st==kv.get_state_name())
            {
                found=true;
                 break;
            }

        }
        if(!found)
        {
            lst<<kv.get_state_name();
        }
    }
    for(auto &x:lst)
    {
        text+="******** State:"+x+"*********\n";
        text+="\n";
        QStringList data=this->get_countries_by_state(x);
        for(auto &y:data)
        {
            int total=this->get_total_country_votes(y,x);
            QStringList pr=this->get_precents_by_country(y,x);
            for(auto &kl:pr)
            {
                QStringList str=kl.split("-");
                double prc=(str[1].toDouble()/total)*100.0;
                text+="############ Country:"+y+"#############\n";
                text+="PARTY:"+str[0]+"   PRECENT:"+QString::number(prc)+"%\n";
            }
            text+="######################################\n";
        }
        text+="\n";
        text+="****************************************<br>";
    }
    return text;
}

QStringList MainWindow::get_precents_by_country(QString cnty,QString state)
{
    QStringList info;
    for(auto &x:results)
    {
        if(x.get_country_name()==cnty && x.get_state_name()==state)
        {
            info<<x.getParty()+"-"+QString::number(x.get_votecount());
        }
    }
    return info;
}

size_t MainWindow::get_total_country_votes(QString cnty,QString state)
{
   int votes=0;
   for(auto &x:results)
   {
       if(x.get_country_name()==cnty && x.get_state_name()==state)
       {
           votes=x.getCountrytottalvote();
           break;
       }
   }
   return votes;
}

void MainWindow::showgraph()
{
   series->clear();
   chart->removeSeries(series);
   QPushButton *send=(QPushButton *)sender();
   QString key=send->property("country").toString();
   QStringList check=key.split("-");
   chart->setTitle("Chart for Country:"+key);
   QColor colors[5]={QColor(Qt::red),QColor(Qt::green),QColor(Qt::blue),QColor(Qt::black),QColor(Qt::darkRed)};
   size_t total=this->get_total_country_votes(check[0],check[1]);
   qDebug()<<total;
   QStringList list=this->get_precents_by_country(check[0],check[1]);
   for(int i=0;i<list.size();i++)
   {
       QStringList splitstr=list[i].split("-");
       QPieSlice *newslice=new QPieSlice(splitstr[0],splitstr[1].toDouble());
       newslice->setBrush(colors[i]);
       double pr=(splitstr[1].toDouble()/total)*100.0;
       newslice->setLabel(splitstr[0]+"-"+QString::number(pr,'f',3));
       series->append(newslice);
   }
   chart->addSeries(series);
}

void MainWindow::mslot(QAction *a)
{
    if(a->text()=="EXPORT")
    {
        QString fn=QFileDialog::getSaveFileName(this,"save chart",".","png files (*.png)");
        if(fn.size()!=0)
      {
            QPixmap save=view->grab();
            save.save(fn,"png");
        }
    }
    else if(a->text()=="BACK")
    {
        int index=ml->currentIndex();
        if(index!=0)
        {
            index--;
        }
        ml->setCurrentIndex(index);
    }
    else if(a->text()=="SAVE")
    {
        QString fn=QFileDialog::getSaveFileName(this,"Save csv",".","txt files (*.csv *.csv)");
        if(fn.size()==0) return;
        QFile sv(fn);
        sv.open(QIODevice::WriteOnly);
        QTextStream stream(&sv);
        stream<<this->file_saving_mode();
        sv.close();
    }
    else if(a->text()=="QUIT")
    {
        qApp->exit(EXIT_SUCCESS);
    }
}
