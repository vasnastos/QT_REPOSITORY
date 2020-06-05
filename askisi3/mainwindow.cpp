#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(700,700);
    this->setWindowTitle("FILE INFOS");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    layout =new QVBoxLayout;
    mw->setLayout(layout);
    QLabel *image=new QLabel;
    QPixmap pix(":/university.png");
    image->setStyleSheet("border-style:2 px-solid;");
    image->setPixmap(pix.scaled(image->size()));
    image->setFixedWidth(0.98 * this->width());
    image->setFixedHeight(0.60 * this->height());
    layout->addWidget(image);
    lesson=new QComboBox;
    lesson->setFixedWidth(0.46 * this->width());
    connect(lesson,SIGNAL(activated(QString)),this,SLOT(lessondetails(QString)));
    QPushButton *b=new QPushButton;
    b->setText("SHOW PASS ALL");
    make_menu();
    QHBoxLayout *r1=new QHBoxLayout;
    layout->addLayout(r1);
    r1->addWidget(lesson);
    r1->addWidget(b);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(show_pass_slot()));
    QStringList list;
    table=new QTableWidget;
    list<<"ID"<<"FULLNAME"<<"GRADE";
    table->setColumnCount(list.size());
    table->setFixedHeight(0.20 * this->height());
    table->setFixedWidth(0.98 * this->width());
    table->setHorizontalHeaderLabels(list);
    layout->addWidget(table);
}

void MainWindow::make_menu()
{
    QMenu *fn=new QMenu("FILE");
    fn->addAction("LOAD");
    fn->addAction("SAVE");
    fn->addAction("QUIT");
    menuBar()->addMenu(fn);
    connect(fn,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
}

QString student_to_str(const student &s,QVector <student> &stds)
{
   QString st="";
   for(int i=0;i<stds.size();i++)
   {
       if(stds.at(i).id==s.id)
       {
           st+=stds.at(i).lessonname+"---"+QString::number(stds.at(i).grade)+"\n";
       }
       st+="\n";
   }
   return st;
}

void MainWindow::menuslot(QAction *a)
{
    if(a->text()=="LOAD")
    {
        QString fn=QFileDialog::getOpenFileName(this,"FILE OPEN",".","txt,csv files (*.txt,*.csv)");
        if(fn.size()==0)
        {
            QMessageBox::critical(this,"ERROR","<p style=color:red>No file selected</p>");
            return;
        }
        QFile fp(fn);
        bool ok=fp.open(QIODevice::ReadOnly | QIODevice::Text);
        if(!ok)
        {
            return;
        }
        QTextStream st(&fp);
        while(!st.atEnd())
        {
            QString line=st.readLine();
            if(line.startsWith("#")) continue;
            if(line.startsWith("-"))
            {
                QStringList lessons=line.split("-");
                lesson->addItems(lessons);
                continue;
            }
            QStringList list=line.split(",");
            student s;
            if(list.size()!=4) continue;

            s.id=list.at(0).toInt();
            s.fullname=list.at(1);
            s.lessonname=list.at(2);
            s.grade=list[4].toDouble();

            students<<s;
        }
        fp.close();
    }
    else if(a->text()=="SAVE")
    {
        QVector <int> tested;
        QString fn=QFileDialog::getSaveFileName(this,"FILE Save",".","txt,csv files (*.txt,*.csv)");
        if(fn.size()==0)
        {
            QMessageBox::critical(this,"ERROR","<p style=color:red>No file selected</p>");
            return;
        }
        QFile fp(fn);
        fp.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream st(&fp);
        for(int i=0;i<students.size();i++)
        {
            int found=0;
            for(int j=0;j<tested.size();j++)
            {
                if(students.at(i).id==tested.at(j))
                {
                    found=1;
                    break;
                }
            }
            if(found==1) continue;
           st<<students.at(i).id<<"\t"<<students.at(i).fullname<<endl;
           st<<student_to_str(students.at(i),students)<<endl;
           tested<<students.at(i).id;
        }
        fp.close();
    }
    else
    {
        qApp->exit();
    }
}

MainWindow::~MainWindow() {}

void MainWindow::lessondetails(QString x)
{
    int counter=0;
    for(int i=0;i<students.size();i++)
    {
        if(students.at(i).lessonname==x)
        counter++;
    }
    table->setRowCount(counter);
    grbox.clear();
    for(int i=0;i<students.size();i++)
    {
        if(students.at(i).lessonname==x)
        {
            table->setItem(i,0,new QTableWidgetItem(QString::number(students.at(i).id)));
            table->setItem(i,1,new QTableWidgetItem(students.at(i).fullname));
            grbox.append(new QDoubleSpinBox);
            grbox[i]->setRange(0.0,10.0);
            grbox[i]->setValue(students.at(i).grade);
            table->setCellWidget(i,2,grbox[i]);
            QPushButton *but=new QPushButton;
            but->setText("UPDATE");
            but->setProperty("upd",i);
            table->setCellWidget(i,4,but);
            connect(but,SIGNAL(clicked(bool)),this,SLOT(updateslot()));
        }
    }
}

void MainWindow::updateslot()
{
    QPushButton *b=(QPushButton *)sender();
    int i=b->property("upd").toInt();
    students[i].grade=grbox[i]->value();
}
 void MainWindow::show_pass_slot()
 {
     table->clear();
     QStringList list;
     list<<"ID"<<"FULLNAME"<<"LESSONNAME"<<"GRADE";
     table->setColumnCount(list.size());
     table->setHorizontalHeaderLabels(list);
     int counter=0;
     for(int i=0;i<students.size();i++)
     {
         if(students.at(i).grade>5.0)
         {
             counter++;
         }
     }
     table->setRowCount(counter);
     for(int i=0;i<students.size();i++)
     {
         if(students.at(i).grade>5.0)
         {
             table->setItem(i,0,new QTableWidgetItem(QString::number(students[i].id)));
             table->setItem(i,1,new QTableWidgetItem(students[i].fullname));
             table->setItem(i,2,new QTableWidgetItem(students[i].lessonname));
             table->setItem(i,3,new QTableWidgetItem(QString::number(students[i].grade)));
         }
     }
 }
