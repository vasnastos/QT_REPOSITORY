#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    this->setFixedSize(600,400);
    this->setWindowTitle("BEMO LESSON");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QStackedLayout;
    makemenu();
    tab1();
    tab2();
    tab3();
}

MainWindow::~MainWindow() {}
void MainWindow::makemenu()
{
    fn=new QMenu("EDIT");
    fn->addAction("Insert window");
    fn->addAction("Save Window");
    fn->addAction("Precent Window");
    menuBar()->addMenu(fn);
    connect(fn,SIGNAL(triggered(QAction *)),this,SLOT(tabsl(QAction *)));
}
void MainWindow::tab1()
{
    QWidget *wid=new QWidget;
    wid->setFixedSize(this->width(),this->height());
    ml->addWidget(wid);
    QHBoxLayout *lay=new QHBoxLayout;
    wid->setLayout(lay);
    QPushButton *b=new QPushButton;
    b->setText("LOAD INFO");
    label=new QLabel;
    label->setFixedSize(100,100);
    label->setStyleSheet("background-color:blue;");
    label->setAlignment(Qt::AlignCenter);
    lay->addWidget(b);
    lay->addWidget(label);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(load()));
}
void MainWindow::tab2()
{
    QWidget *widg=new QWidget;
    widg->setFixedSize(this->width(),this->height());
    ml->addWidget(widg);
    QHBoxLayout *lay=new QHBoxLayout;
    widg->setLayout(lay);
    QPushButton *b=new QPushButton;
    b->setText("SAVE INFO");
    lab1=new QLabel;
    lab1->setFixedSize(100,100);
    lab1->setStyleSheet("background-color:blue;");
    lab1->setAlignment(Qt::AlignCenter);
    lay->addWidget(b);
    lay->addWidget(lab1);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(save()));
}
void MainWindow::tab3()
{
    QWidget *w=new QWidget;
    w->setFixedSize(this->width(),this->height());
    ml->addWidget(w);
    QVBoxLayout *lay=new QVBoxLayout;
    w->setLayout(lay);
    QHBoxLayout *l1=new QHBoxLayout;
    lay->addLayout(l1);
    s=new QLineEdit;
    s->setPlaceholderText("Give lesson name:");
    QPushButton *button=new QPushButton;
    button->setText("SEARCH");
    l1->addWidget(s);
    l1->addWidget(button);
    connect(button,SIGNAL(clicked(bool)),this,SLOT(search()));
    tab=new QTableWidget;
    lay->addWidget(tab);
}
void MainWindow::load()
{
    QString fn=QFileDialog::getOpenFileName(this,"GIVE DATA TO DB",".","(txt files) (*.txt,*.csv)");
    if(fn.size()==0) return;
    QFile fp(fn);
    if(!fp.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream st(&fp);
    int id;
    QString name;
    double gr;
    bool ok,ok1;
    while(!st.atEnd())
    {
        QString line=st.readLine();
        QStringList lst=line.split(",");
        if(lst.size()!=3) continue;
        id=lst[0].toInt(&ok);
        name=lst[1];
        gr=lst[2].toDouble(&ok1);
        if(!ok || !ok1) continue;
        lesson l(id,name,gr);
        mydb->insert(l);
    }
    label->setText("<p style=color:red>insertion from "+fn+" complete</p>");
    fp.close();
}
void MainWindow::save()
{
    QString fn=QFileDialog::getOpenFileName(this,"SAVE DATA FROM DB",".","(txt files) (*.txt,*.csv)");
    if(fn.size()==0) return;
    QFile fp(fn);
    if(!fp.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream st(&fp);
    QVector <QString> ln=mydb->getlessonnames();
    QVector <detail> details;
    for(int i=0;i<ln.size();i++)
    {
        st<<"LESSON:"+ln.at(i)<<endl;
        details.clear();
        details=mydb->getlessondetails(ln.at(i));
        if(details.size()==0) continue;
        for(int j=0;j<details.size();j++)
        {
            st<<details.at(j).id<<","<<details.at(j).gr<<endl;
        }
    }
    lab1->setText("<p style=color:red>details have been saved to "+fn+"</p>");
    fp.close();
}
void MainWindow::search()
{
   QStringList header;
   header<<"ID"<<"GRADE";
   tab->setColumnCount(header.size());
   if(s->text().isEmpty())
   {
       QMessageBox::critical(this,"ERROR","FILL ALL THE BLANKS");
       return;
   }
   QVector <detail> dets=mydb->getlessondetails(s->text());
   if(dets.size()==0)
   {
       QMessageBox::critical(this,"ERROR","No students enrolled in this lesson");
       return;
   }
   tab->setRowCount(dets.size());
   for(int i=0;i<tab->rowCount();i++)
   {
       tab->setItem(i,0,new QTableWidgetItem(QString::number(dets.at(i).id)));
       tab->setItem(i,1,new QTableWidgetItem(QString::number(dets.at(i).gr)));
   }
}
void MainWindow::tabsl(QAction *a)
{
    if(a->text()=="Insert window")
    {
        ml->setCurrentIndex(0);
    }
    else if(a->text()=="Save Window")
    {
        ml->setCurrentIndex(1);
    }
    else
    {
        ml->setCurrentIndex(2);
    }
}
