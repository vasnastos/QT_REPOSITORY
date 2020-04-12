#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent): QMainWindow(parent)
{
    QDesktopWidget *qd=new QDesktopWidget;
    this->setFixedSize(qd->geometry().width()/2,qd->geometry().height()/2);
    this->setWindowTitle("DEMO_2");
    mw=new QWidget;
    this->setCentralWidget(mw);
    mw->setFixedSize(this->width(),this->height());
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    bar=new QMenuBar;
    fm=new QMenu("FILE");
    fm->addAction("LOAD");
    fm->addAction("SAVE");
    fm->addAction("QUIT");
    bar->addMenu(fm);
    ml->addWidget(bar);
    connect(fm,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
    int i=QInputDialog::getInt(this,"Give Lesson!!","Please give number of lessons");
    for(int j=0;j<i;j++)
    {
        QHBoxLayout *rt=new QHBoxLayout;
        ml->addLayout(rt);
        QSlider *sld=new QSlider(Qt::Horizontal);
        sld->setMaximum(10);
        sld->setMinimum(0);
        sld->setTickInterval(1);
        sld->setProperty("val",j);
        sl<<sld;
        connect(sld,SIGNAL(valueChanged(int)),this,SLOT(priceslot(int)));
        rt->addWidget(sld);
        QLabel *k=new QLabel;
        k->setText("GRADE:0");
        lb<<k;
        rt->addWidget(k);
    }
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    id=new QLineEdit;
    id->setPlaceholderText("Give Id");
    id->setValidator(new QIntValidator(1000,17890));
    n=new QLineEdit;
    n->setPlaceholderText("Give Name");
    r1->addWidget(id);
    r1->addWidget(n);
    b=new QPushButton;
    b->setText("ADD");
    b1=new QPushButton;
    b1->setText("SORT");
    QHBoxLayout *r2=new QHBoxLayout;
    ml->addLayout(r2);
    r2->addWidget(b);
    r2->addWidget(b1);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(addslot()));
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(sortslot()));
    tab=new QTableWidget;
    QStringList l;
    l<<"ID"<<"NAME";
    for(int j=0;j<i;j++)
    {
        l<<"LESSON_"+QString::number(j+1);
    }
    l<<"AVERAGE";
    tab->setColumnCount(l.size());
    tab->setHorizontalHeaderLabels(l);
    ml->addWidget(tab);
    connect(this,SIGNAL(tabshow()),this,SLOT(tablechanges()));
}

mainwindow::~mainwindow() {}
void mainwindow::tablechanges()
{
   tab->setRowCount(students.size());
   for(int i=0;i<tab->rowCount();i++)
   {
       tab->setItem(i,0,new QTableWidgetItem(QString::number(students[i].id)));
       tab->setItem(i,1,new QTableWidgetItem(students[i].name));
       for(int j=0;j<students[i].grades.size();j++)
       {
           tab->setItem(i,j+2,new QTableWidgetItem(QString::number(students[i].grades[j])));
       }
       tab->setItem(i,tab->columnCount()-1,new QTableWidgetItem(QString::number(students[i].avg)));
   }
}
void mainwindow::addslot()
{
    for(int i=0;i<students.size();i++)
    {
        if(id->text().toInt()==students[i].id)
        {
            students[i].avg=0.0;
            for(int j=0;j<students[i].grades.size();j++)
            {
                students[i].grades[j]=sl[j]->value();
                students[i].avg+=sl[j]->value();
            }
            students[i].avg/=students[i].grades.size()*1.0;
            QMessageBox::information(this,"INFO","Student has been MODIFIED");
            emit tabshow();
            return;
        }
    }
    if(id->text().isEmpty() || n->text().isEmpty())
    {
        QMessageBox::critical(this,"ERROR","Fill the blanks");
    }
    else
    {
        student s;
        s.id=id->text().toInt();
        s.name=n->text();
        s.avg=0;
        for(int i=0;i<sl.size();i++)
        {
            s.grades.append(sl[i]->value());
            s.avg+=sl[i]->value();
        }
        s.avg/=s.grades.size();
        students<<s;//like append.
        emit tabshow();
    }
}
void mainwindow::sortslot()
{
    int size=students.size();
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size-1;j++)
        {
            if(students[j]>students[j+1])
            {
                student *temp=new student;
                *temp=students[j];
                 students[j]=students[j+1];
                 students[j+1]=*temp;
                 delete temp;
            }
        }
    }
    QMessageBox::information(this,"sort","SORT COMPLETED");
    emit tabshow();
}
void mainwindow::menuslot(QAction *ac)
{
    if(ac->text()=="LOAD")
    {
        QString fn=QFileDialog::getOpenFileName(this,"<b>OPEN FILE</b>","..","txt files,(*.txt)");
        if(fn.size()==0)
        {
            QMessageBox::critical(this,"ERROR","No file open");
        }
        QFile fp(fn);
        if(!fp.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::critical(this,"ERROR","FILE NOT OPEN FOR READING");
            return;
        }
        QTextStream st(&fp);
        while(!st.atEnd())
        {
            bool ok,ok1;
            QString line=st.readLine();
            QStringList lst=line.split(",");
            student s;
            s.id=lst[0].toInt(&ok);
            if(!ok) continue;
            s.name=lst[1];
            int f=0;
            for(int i=2;i<lst.size()-1;i++)
            {
                s.grades.append(lst[i].toInt(&ok1));
                if(!ok1)
                {
                    QMessageBox::critical(this,"ERROR","Incorrect data");
                    f=1;
                    break;
                }
            }
            if(f==1) continue;
            bool ok2;
            bool fn=false;
            s.avg=lst[lst.size()-1].toDouble(&ok2);
            if(!ok2) continue;
            for(int i=0;i<students.size();i++)
            {
                if(students[i].id==s.id)
                {
                    QMessageBox::critical(this,"ERROR","Student have been already enrolled in class");
                    fn=true;
                    break;
                }
            }
            if(fn) continue;
            else
            {
              students.append(s);
              QMessageBox::information(this,"Enroll","<b>NEW STUDENT ENROLLED IN CLASS</b>");
            }
        }
        fp.close();
        emit tablechanges();
    }
    else if(ac->text()=="SAVE")
    {
        QString fn=QFileDialog::getSaveFileName(this,"<b>SAVE FILE</b>","..","txt files,(*.txt)");
        if(fn.size()==0)
        {
            QMessageBox::critical(this,"error","you did not seletct a file to save");
            return;
        }
        QFile fp(fn);
        if(!fp.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::critical(this,"ERROR","FILE NOT OPEN FOR SAVING");
            return;
        }
        QTextStream st(&fp);
        for(int i=0;i<students.size();i++)
        {
            st<<students[i].tostring()<<endl;
        }
        QMessageBox::information(this,"FILE SAVE","TO:"+fn);
    }
    else
    {
        exit(EXIT_SUCCESS);
    }
}
void mainwindow::priceslot(int v)
{
    QSlider *b=(QSlider *)sender();
    int i=b->property("val").toInt();
    lb[i]->setText("GRADE:"+QString::number(v));
}
