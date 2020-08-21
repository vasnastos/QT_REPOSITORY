#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,600);
    this->setWindowTitle("Stack Widget Example");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    b=new QPushButton("LOAD");
    b->setFixedWidth(0.2*width());
    s=new QPushButton;
    s->setText("PASS");
    s->setFixedWidth(0.2*width());
    QHBoxLayout *r=new QHBoxLayout;
    ml->addLayout(r);
    r->addWidget(b);
    r->addWidget(s);
    shwd=new QStackedWidget;
    pass=new QTableWidget;
    pass->setFixedWidth(0.5*width());
    pass->setStyleSheet("border:2px solid;");
    QStringList dets;
    dets<<"ID"<<"GRADE";
    pass->setColumnCount(dets.size());
    pass->setHorizontalHeaderLabels(dets);
    pass->setColumnWidth(0,0.45*pass->width());
    pass->setColumnWidth(1,0.45*pass->width());
    fail=new QTableWidget;
    fail->setFixedWidth(0.5*width());
    fail->setStyleSheet("border:2px solid;");
    fail->setColumnCount(dets.size());
    fail->setHorizontalHeaderLabels(dets);
    fail->setColumnWidth(0,0.45*fail->width());
    fail->setColumnWidth(1,0.45*fail->width());
    shwd->addWidget(pass);
    shwd->addWidget(fail);
    chr=new QChart;
    srs=new QPieSeries;
    chr->addSeries(srs);
    view=new QChartView;
    view->setChart(chr);
    view->setRenderHint(QPainter::Antialiasing);
    view->setStyleSheet("border:2px solid;"
                        "border-color:red");
    QHBoxLayout *row=new QHBoxLayout;
    ml->addLayout(row);
    row->addWidget(shwd);
    row->addWidget(view);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(s,SIGNAL(clicked(bool)),this,SLOT(changewidget()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"Load grades",".","(text files) (*.txt *.csv)");
    if(fn.size()==0) return;
    srs->clear();
    students.clear();
    pass->clearContents();
    fail->clearContents();
    QFile fp(fn);
    fp.open(QIODevice::ReadOnly);
    QTextStream st(&fp);
    int counter=0;
    QVector <student> pst,fst;
    while(!st.atEnd())
    {
        QString line=st.readLine();
        counter++;
        if(counter==1)
        {
            chr->setTitle("<h4>Lesson:"+line+"</h4>");
            continue;
        }
        if(counter==2)
        {
            QStringList data=line.split(",");
            if(data.size()!=2)
            {
                QMessageBox::critical(this,"Error","No percents of lesson loaded");
                return;
            }
            thp=data[0].toDouble();
            lbp=data[1].toDouble();
            continue;
        }
        QStringList data=line.split(",");
        student s;
        s.am=data[0];
        s.theory=data[1].toDouble();
        s.lab=data[2].toDouble();
        students<<s;
        if((s.theory*(thp/100.0))+(s.lab*(lbp/100.0))>=5.0)
        {
            pst.append(s);
        }
        else
        {
            fst.append(s);
        }
    }
    fp.close();
    pass->setRowCount(pst.size());
    fail->setRowCount(fst.size());
    for(int i=0;i<pass->rowCount();i++)
    {
        pass->setItem(i,0,new QTableWidgetItem(pst[i].am));
        double finalgrade=pst.at(i).theory*(thp/100.0)+pst.at(i).lab*(lbp/100.0);
        pass->setItem(i,1,new QTableWidgetItem(QString::number(finalgrade,'f',2)));
    }
    for(int i=0;i<fail->rowCount();i++)
    {
        fail->setItem(i,0,new QTableWidgetItem(fst[i].am));
        double finalgrade=fst.at(i).theory*(thp/100.0)+fst.at(i).lab*(lbp/100.0);
        fail->setItem(i,1,new QTableWidgetItem(QString::number(finalgrade,'f',2)));
    }
    chr->removeSeries(srs);
    srs->clear();
    double passrate=((pst.size()*1.0)/students.size())*100.0;
    double failrate=((fst.size()*1.0)/students.size())*100.0;
    QPieSlice *s1=new QPieSlice("Pass",passrate);
    QPieSlice *s2=new QPieSlice("Fail",failrate);

    s1->setLabel("pass:"+QString::number(passrate,'f',2));
    s1->setLabelColor(Qt::green);
    s2->setLabel("fail:"+QString::number(failrate,'f',2));
    s2->setLabelColor(Qt::red);
    s2->setBrush(Qt::darkRed);
    s1->setBrush(Qt::darkGreen);
    srs->append(s1);
    srs->append(s2);
    chr->addSeries(srs);
}


void MainWindow::changewidget()
{
    if(s->text()=="PASS")
    {
        shwd->setCurrentIndex(0);
        s->setText("FAIL");
    }
    else
    {
        shwd->setCurrentIndex(1);
        s->setText("PASS");
    }
}
