#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QDesktopWidget *desktop=new QDesktopWidget;
    this->setFixedSize(desktop->geometry().width()/2,desktop->geometry().height()/2);
    this->setWindowTitle("PREPARATION_WINDOW");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    tw=new QTabWidget;
    ml->addWidget(tw);
    tab1();
    tab2();
}

void MainWindow::tab1()
{
    QWidget *tw1=new QWidget;
    tw1->setFixedSize(this->width(),this->height());
    tw->addTab(tw1,"MENU");
    QVBoxLayout *twl=new QVBoxLayout;
    tw1->setLayout(twl);
    QHBoxLayout *r1=new QHBoxLayout;
    twl->addLayout(r1);
    QPushButton *b=new QPushButton;
    b->setText("LOAD");
    QPushButton *b1=new QPushButton;
    b1->setText("SAVE");
    QPushButton *b2=new QPushButton;
    b2->setText("EXPORT");
    r1->addWidget(b);
    r1->addWidget(b1);
    r1->addWidget(b2);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(saveslot()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(exportslot()));
    cb=new QComboBox;
    QHBoxLayout *r2=new QHBoxLayout;
    twl->addLayout(r2);
    ed=new QTextEdit;
    r2->addWidget(cb);
    r2->addWidget(ed);
    connect(cb,SIGNAL(activated(QString)),this,SLOT(comboslot(QString)));
    QString edtext=read_copyright();
    ed->setText(edtext);
}

void MainWindow::tab2()
{
    QWidget *tw2=new QWidget;
    tw2->setFixedSize(this->width(),this->height());
    tw->addTab(tw2,"SHOWTAB");
    QVBoxLayout *twl=new QVBoxLayout;
    tw2->setLayout(twl);
    QLabel *lb=new QLabel;
    QPixmap *pix=new QPixmap(":/school.png");
    lb->setPixmap(pix->scaled(lb->size()));
    lb->setFixedWidth(0.98 * this->width());
    twl->addWidget(lb);
    tab=new QTableWidget;
    tab->setFixedWidth(0.98 * this->width());
    twl->addWidget(tab);
}

QString read_copyright()
{
  QString n="";
  QFile fp(":/copyright.txt");
  bool ok=fp.open(QIODevice::ReadOnly | QIODevice::Text);
  if(!ok) return "";
  QTextStream st(&fp);
  while(!st.atEnd())
  {
      QString line=st.readLine();
      n+=line+"\n";
  }
  fp.close();
  return n;
}

bool MainWindow::lesson_is_in(const student &s)
{
  for(int i=0;i<lessons.size();i++)
  {
      if(lessons[i]==s.get_lname())
      {
        return true;
      }
  }
  return false;
}

void MainWindow::get_lessons()
{
    for(int i=0;i<lessons.size();i++)
    {
        bool ok=this->lesson_is_in(students[i]);
        if(ok) continue;
        else
            lessons.append(students[i].get_lname());
    }
}

MainWindow::~MainWindow() {}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"FILE OPEN",".","txt,csv files (*.txt),(*.csv)");

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
        if(line.startsWith("#"))
        {
            continue;
        }
        if(line.size()==0)
        {
            continue;
        }
        QStringList data=line.split("-");
        if(data.size()!=4)
        {
            continue;
        }
        student s(data[0].toInt(),data[1],data[2],data[3].toDouble());
        students<<s;
    }
    fp.close();
}

void MainWindow::saveslot()
{
    QStringList lst;
    lst<<"ID"<<"NAME"<<"LESSONAME"<<"GRADE";
    tab->setColumnCount(lst.size());
    tab->setHorizontalHeaderLabels(lst);
    QString fn=QFileDialog::getSaveFileName(this,"SAVE FILE",".","txt,csv files (*.txt),(*.csv)");

    if(fn.size()==0 || students.size())
    {
        QMessageBox::critical(this,"SAVE","ERROR No file detected");\
        return;
    }
    QFile fp(fn);

    fp.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream st(&fp);

    for(int i=0;i<students.size();i++)
    {
        st<<students[i].to_str()<<endl;
    }
    fp.close();
}

void MainWindow::exportslot()
{
    QString fn=QFileDialog::getSaveFileName(this,"SAVE IMAGE",".","png files (*.png)");

    if(fn.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No file choose please choose a file");
        return;
    }
    else
    {
        QPixmap pix=tab->grab();
        pix.save(fn,"png");
    }
}

void MainWindow::comboslot(QString x)
{
    int counter=0;
    tab->clear();
    QStringList lst;
    lst<<"ID"<<"FULLNAME"<<"GRADE";
    tab->setColumnCount(lst.size());
    tab->setHorizontalHeaderLabels(lst);
    for(int i=0;i<students.size();i++)
    {
        if(students[i].get_lname()==x)
        {
            counter++;
        }
    }
    tab->setRowCount(counter);
    for(int i=0;i<students.size();i++)
    {
        if(students[i].get_lname()==x)
        {
            tab->setItem(i,0,new QTableWidgetItem(QString::number(students[i].get_id())));
            tab->setItem(i,1,new QTableWidgetItem(students[i].get_fullname()));
            tab->setItem(i,2,new QTableWidgetItem(QString::number(students[i].get_grade())));
        }
    }
}
