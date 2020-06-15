#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(500,500);
    this->setWindowTitle("Bank DEMO");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    tab=new QTabWidget;
    ml->addWidget(tab);
    tab1();
    tab2();
}

void MainWindow::tab1()
{
    QWidget *tw1=new QWidget;
    tw1->setFixedSize(this->width(),this->height());
    tab->addTab(tw1,"GENERAL");
    QVBoxLayout *layout=new QVBoxLayout;
    tw1->setLayout(layout);
    QHBoxLayout *r1=new QHBoxLayout;
    QLabel *label=new QLabel;
    label->setText("LOAD AND INFO");
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("backgroung-color:Lime;");
    layout->addWidget(label);
    layout->addLayout(r1);
    QPushButton *loadbutton=new QPushButton;
    loadbutton->setText("LOAD");
    QPushButton *savebutton=new QPushButton;
    savebutton->setText("SAVE");
    QPushButton *quitbutton=new QPushButton;
    quitbutton->setText("QUIT");
    r1->addWidget(loadbutton);
    r1->addWidget(savebutton);
    r1->addWidget(quitbutton);
    connect(loadbutton,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(savebutton,SIGNAL(clicked(bool)),this,SLOT(saveslot()));
    connect(quitbutton,SIGNAL(clicked(bool)),this,SLOT(quitslot()));
}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"OPEN FILE",".","txt,csv files (*.txt,*csv)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"ERROR","<p style=color:red>No such file selected</p>");
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
        if(line.startsWith("\n")) continue;
        QStringList data=line.split("-");
        account acc(data[0]);
        for(int i=1;i<data.size();i++)
        {
            acc.add_account(data[i].toDouble());
        }
        accounts<<acc;
    }
    fp.close();
    for(int i=0;i<accounts.size();i++)
    {
        this->accountnumbers.append(accounts[i].getaccnumber());
    }
}

void MainWindow::saveslot()
{
   QString fn=QFileDialog::getSaveFileName(this,"SAVE SLOT",".","txt,csv files (*.txt,*.csv)");
   if(fn.size()==0)
   {
       QMessageBox::critical(this,"ERROR","<p style=color:red>No such file selected</p>");
       return;
   }
   QFile fp(fn);
   fp.open(QIODevice::WriteOnly | QIODevice::Text);
   QTextStream st(&fp);
   for(int i=0;i<accounts.size();i++)
   {
       st<<accounts[i].to_str()<<endl;
   }
   fp.close();
}

void MainWindow::quitslot()
{
    qApp->exit();
}

MainWindow::~MainWindow() {}

void MainWindow::tab2()
{
    QWidget *tw2=new QWidget;
    tw2->setFixedSize(this->width(),this->height());
    tab->addTab(tw2,"SHOW CONNECTED");
    QVBoxLayout *lay=new QVBoxLayout;
    tw2->setLayout(lay);
    QPushButton *but=new QPushButton;
    but->setText("Login");
    but->setFixedWidth(0.50 * this->width());
    showlabel=new QLabel;
    showlabel->setStyleSheet("border-style:2px solid;");
    lay->addWidget(but);
    lay->addWidget(showlabel);
    connect(but,SIGNAL(clicked(bool)),this,SLOT(searchslot()));
}

void MainWindow::searchslot()
{
    QString key;
    dialog d(accountnumbers);
    d.exec();
    if(d.forceclose())
    {
         d.close();
        return;
    }
    else if(d.exec()==QDialog::Accepted)
    {
       key=d.getconnect();
    }
    for(int i=0;i<accounts.size();i++)
    {
        if(accounts[i].getaccnumber()==key)
        {
            showlabel->clear();
            showlabel->setText("<p style=color:red>"+accounts[i].to_str()+"</p>");
            break;
        }
    }
}
