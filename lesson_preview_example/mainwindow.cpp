#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800,900);
    this->setWindowTitle("Lesson Handler");
    this->setWindowIcon(QIcon(QIcon(":/central.png")));
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lb=new QLabel;
    lb->setFixedSize(0.95 * width(),0.3 * height());
    QPixmap p(":/window.png");
    lb->setPixmap(p.scaled(lb->width(),lb->height()));
    lb->setStyleSheet("border:2px solid; "
                      "border-color:red;");
    ml->addWidget(lb);
    make_menu();

    tab=new QTableWidget;
    tab->setFixedSize(0.95 * width(),0.2 * height());
    QStringList header;
    header<<"ID"<<"THEORY"<<"LAB"<<"TOTAL";
    tab->setColumnCount(header.size());
    tab->setHorizontalHeaderLabels(header);
    ml->addWidget(tab);
    chart=new QChart();
    series=new QPieSeries();
    chart->addSeries(series);
    view=new QChartView(chart);
    view->setFixedSize(0.95 * width(),0.4 * height());
    ml->addWidget(view);
    mydb=new database;
}

void MainWindow::make_menu()
{
    QMenu *men=new QMenu("File");
    QMenu *men1=new QMenu("Edit");
    QIcon ic1(":/load.png");
    QIcon ic2(":/save.png");
    QIcon ic3(":/export.png");
    men->addAction(ic1,"Load");
    men->addAction(ic2,"Save");
    men->addAction(ic3,"Export");
    men->addAction(QIcon(":/chart.png"),"Chart");
    men1->addAction(QIcon(":/db.png"),"Load");
    men1->addAction(QIcon(":/exit.png"),"Quit");
    menuBar()->addMenu(men);
    menuBar()->addMenu(men1);
    connect(men,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
    connect(men1,SIGNAL(triggered(QAction *)),this,SLOT(menuslot1(QAction *)));
}

MainWindow::~MainWindow() {delete mydb;}

void MainWindow::menuslot(QAction *a)
{
   if(a->text()=="Load")
   {
       loadedfromdb=false;
       students.clear();
      QString fn=QFileDialog::getOpenFileName(this,"Open file",".","csv files (*.csv)");
      if(fn.size()==0)
      {
          QMessageBox::critical(this,"ERROR","<p style=text-algn:center; color:red>No file selected</p>");
          return;
      }
      QFile ifst(fn);
      bool ok=ifst.open(QIODevice::ReadOnly | QIODevice::Text);
      if(!ok) return;
      QTextStream st(&ifst);
      int counter=0;
      while(!st.atEnd())
      {
          counter++;
          QString line=st.readLine();
          if(counter==1)
          {
              this->lesson=line;
              continue;
          }
          if(counter==2)
          {
              QStringList lst=line.split(",");
              precenttheory=lst[0].toDouble()/100;
              precentlab=lst[1].toDouble()/100;
              continue;
          }
          QStringList data=line.split(",");
          if(data.size()!=3)
          {
             continue;
          }
          student s;
          s.id=data[0].toInt();
          s.gradetheory=data[1].toDouble();
          s.gradelab=data[2].toDouble();
          students<<s;
          double fg=s.gradelab*precentlab+s.gradetheory*precenttheory;
          mydb->insert_lesson(lesson,data[0].toInt(),fg);
      }
      ifst.close();
      tab->clear();
      QStringList header;
      header<<"ID"<<"THEORY"<<"LAB"<<"TOTAL";
      tab->setColumnCount(header.size());
      tab->setHorizontalHeaderLabels(header);
      tab->setRowCount(students.size());
      for(int i=0;i<tab->rowCount();i++)
      {
          tab->setItem(i,0,new QTableWidgetItem(QString::number(students[i].id)));
          tab->setItem(i,1,new QTableWidgetItem(QString::number(students[i].gradetheory)));
          tab->setItem(i,2,new QTableWidgetItem(QString::number(students[i].gradelab)));
          QPushButton *b=new QPushButton;
          b->setText("Final");
          b->setStyleSheet("padding: 5px 10px;"
                           "font-size: 14px;"
                           "text-align: center;"
                           "color: #fff;"
                           "background-color: #4CAF50;"
                           "border: none;"
                           "border-radius: 8px;");
          b->setProperty("id",students[i].id);
          tab->setCellWidget(i,3,b);
          connect(b,SIGNAL(clicked(bool)),this,SLOT(showfinal()));
      }
   }
   else if(a->text()=="Save")
   {
     QString fn=QFileDialog::getSaveFileName(this,"Save file",".","csv files (*.csv)");
     if(fn.size()==0)
     {
         QMessageBox::critical(this,"ERROR","No file selected");
         return;
     }
     QFile fp(fn);
     fp.open(QIODevice::WriteOnly);
     QTextStream stream(&fp);
     stream<<"File created at "<<__DATE__<<"  "<<__TIME__<<endl;
     stream<<"Final standings for lesson:"<<lesson<<endl;
     stream<<"************************* Final standings **************************"<<endl;
     if(!loadedfromdb)
     {
      for(auto &x:students)
      {
         stream<<"ID:"<<x.id<<"   ";
         double fg=precenttheory*x.gradetheory+precentlab*x.gradelab;
         stream<<"FINAL GRADE:"<<fg<<endl;
      }
      stream<<"*********************************************************************"<<endl;
     }
     else
     {
        for(auto &x:loadeddetails)
        {
           stream<<"ID:"<<x.id<<"   GRADE:"<<x.fg<<endl;
        }
     }
     fp.close();
   }
   else if(a->text()=="Export")
   {
       QString filename=QFileDialog::getSaveFileName(this,"Save chart",".","image files (*.png)");
       if(filename.size()!=0)
       {
           QPixmap pix=view->grab();
           pix.save(filename,"png");
       }
   }
   else if(a->text()=="Chart")
   {
       double passprecent;
       double failprecent;
      series->clear();
      int p=0,f=0;
      if(loadedfromdb)
      {
         for(auto &y:loadeddetails)
         {
            if(y.fg>=5)
            {
                p++;
            }
            else
            {
                f++;
            }
         }
         passprecent=(double)p/loadeddetails.size()*100;
         failprecent=(double)f/loadeddetails.size()*100;
      }
      else
      {
       for(auto &x:students)
       {
          if(precenttheory*x.gradetheory+precentlab*x.gradelab>=5.0)
          {
              p++;
          }
          else
          {
              f++;
          }
       }
       passprecent=(double)p/students.size()*100;
       failprecent=(double)f/students.size()*100;
      }
      chart->setTitle("<b>Pass-Fail Ratio for "+lesson+"</b>");
      QPieSlice *sl=new QPieSlice("Pass",p);
      sl->setBrush(Qt::green);
      sl->setLabel(QString::number(passprecent)+"%");
      sl->setValue(passprecent);
      QPieSlice *slf=new QPieSlice("Fail",f);
      slf->setBrush(Qt::red);
      slf->setLabel(QString::number(failprecent)+"%");
      slf->setValue(failprecent);
      series->append(sl);
      series->append(slf);
      chart->removeSeries(series);
      chart->addSeries(series);
   }
}

void MainWindow::showfinal()
{
    QPushButton *prop=(QPushButton *)sender();
    int sid=prop->property("id").toInt();
    double fg=0.0;
    for(auto &x:students)
    {
       if(x.id==sid)
       {
           fg=precenttheory*x.gradetheory+precentlab*x.gradelab;
       }
    }
    QMessageBox::information(this,"Final grade of "+QString::number(sid),"<p style=color:blue>Grade:"+QString::number(fg)+"</p>");
}

void MainWindow::menuslot1(QAction *a)
{
    if(a->text()=="Load")
    {
      dialog d(*mydb);
      d.exec();
      loadeddetails=d.getdetsvector();
      if(loadeddetails.size()==0)
      {
          return;
      }
      loadedfromdb=true;
      lesson=d.getselectedlesson();
      tab->clear();
      QStringList header;
      header<<"ID"<<"GRADE";
      tab->setColumnCount(header.size());
      tab->setRowCount(loadeddetails.size());
      tab->setHorizontalHeaderLabels(header);
      int j=0;
      for(auto x:loadeddetails)
      {
        tab->setItem(j,0,new QTableWidgetItem(QString::number(x.id)));
        tab->setItem(j,1,new QTableWidgetItem(QString::number(x.fg)));
        j++;
      }
    }
    else if(a->text()=="Quit")
    {
        qApp->exit(EXIT_SUCCESS);
    }
}
