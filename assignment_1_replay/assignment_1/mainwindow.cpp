#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    this->setFixedSize(600,700);
    this->setWindowTitle("Numbers demo");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *label=new QLabel;
    label->setFixedWidth(0.98 * this->width());
    QPixmap pix(":/numbers.png");
    label->setFixedHeight(0.4 * this->height());
    label->setStyleSheet("border-style:solid;");
    label->setPixmap(pix.scaled(label->width(),label->height()));
    ml->addWidget(label);
    QPushButton *l=new QPushButton;
    l->setText("Load");
    QPushButton *s=new QPushButton;
    s->setText("SAVE");
    QPushButton *c=new QPushButton;
    c->setText("CLEAR CONTENTS");
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    r1->addWidget(l);
    r1->addWidget(s);
    r1->addWidget(c);
    connect(l,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(s,SIGNAL(clicked(bool)),this,SLOT(saveslot()));
    connect(c,SIGNAL(clicked(bool)),this,SLOT(clearslot()));
    tab=new QTableWidget;
    QStringList lst;
    lst<<"SUM"<<"SQRT SUM"<<"AVERAGE"<<"MAX"<<"SHOW";
    tab->setColumnCount(lst.size());
    tab->setHorizontalHeaderLabels(lst);
    ml->addWidget(tab);
}

MainWindow::~MainWindow() {}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"File open",".","txt files (*.txt)");

    if(fn.size()==0) return;

    QFile fp(fn);

    bool ok=fp.open(QIODevice::ReadOnly | QIODevice::Text);

    if(!ok) return;

    QTextStream st(&fp);

    while(!st.atEnd())
    {
        QString line=st.readLine();
        if(line.size()==0) continue;
        if(line.startsWith("#")) continue;

        QStringList data=line.split(",");

        class line nl;
        for(auto &x:data)
        {
          nl.add_number(x.toDouble());
        }
        lines.append(nl);
    }
    fp.close();
    tab->setRowCount(lines.size());
    for(int i=0;i<tab->rowCount();i++)
    {
        QPushButton *b1=new QPushButton;
        b1->setText("SUM");
        b1->setProperty("sum",i);
        tab->setCellWidget(i,0,b1);
        QPushButton *b2=new QPushButton;
        b2->setText("SQRT OF SUM");
        b2->setProperty("sqrt",i);
        tab->setCellWidget(i,1,b2);
        QPushButton *b3=new QPushButton;
        b3->setText("AVERAGE");
        b3->setProperty("av",i);
        tab->setCellWidget(i,2,b3);
        QPushButton *b4=new QPushButton;
        b4->setText("MAX INFO");
        b4->setProperty("max",i);
        tab->setCellWidget(i,3,b4);
        QPushButton *b5=new QPushButton;
        b5->setText("SHOW");
        b5->setProperty("sh",i);
        tab->setCellWidget(i,4,b5);
        connect(b1,SIGNAL(clicked(bool)),this,SLOT(sumslot()));
        connect(b2,SIGNAL(clicked(bool)),this,SLOT(sqrtslot()));
        connect(b3,SIGNAL(clicked(bool)),this,SLOT(averageslot()));
        connect(b4,SIGNAL(clicked(bool)),this,SLOT(maxslot()));
        connect(b5,SIGNAL(clicked(bool)),this,SLOT(showslot()));
    }
}


void MainWindow::saveslot()
{
    QString filename=QFileDialog::getSaveFileName(this,"SAVE FILE",".","txt,csv (*.txt,*.csv)");

    if(filename.size()==0) return;

    QFile fp(filename);

    fp.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream st(&fp);
    st<<"LINE DETAILS BROUGHT BY FILE"<<endl;
    st<<"READ AT::"<<__TIME__<<endl;

    int i=1;
    for(auto &x:lines)
    {
        st<<"Line "<<i<<"::"<<x.to_str()<<endl;
        i++;
    }
    fp.close();
}


void MainWindow::clearslot()
{
    tab->clearContents();
    lines.clear();
    QMessageBox::information(this,"INFO","<p style=color:red>Fetch another file in order to use program again</p>");
}

void MainWindow::sumslot()
{
    QPushButton *pressed=(QPushButton *)sender();
    int pos=pressed->property("sum").toInt();
    QMessageBox::information(this,"SUM OF LINE "+QString::number(pos),"SUM IS:"+QString::number(lines[pos].sum()));
}

void MainWindow::sqrtslot()
{
    QPushButton *pressed=(QPushButton *)sender();
    int pos=pressed->property("sqrt").toInt();
    QMessageBox::information(this,"SQRT OF SUM OF LINE "+QString::number(pos),"SQRT OF SUM IS:"+QString::number(lines[pos].sqrtsum()));
}

void MainWindow::averageslot()
{
    QPushButton *pressed=(QPushButton *)sender();
    int pos=pressed->property("av").toInt();
    QMessageBox::information(this,"AVERAGE OF LINE "+QString::number(pos),"AVERAGE IS:"+QString::number(lines[pos].average()));
}

void MainWindow::maxslot()
{
    QPushButton *pressed=(QPushButton *)sender();
    int pos=pressed->property("max").toInt();
    maxelem pressedmax=lines[pos].find_max();
    QString info;
    info+="MAX:"+QString::number(pressedmax.max)+"\t"+"FOUND IN POSITIONS:";
    for(auto &x:pressedmax.spots)
    {
        info+=QString::number(x)+" ";
    }
    QMessageBox::information(this,"MAX AND MAX INDEXEES OF LINE "+QString::number(pos),"MAX INFO:"+info);
}

void MainWindow::showslot()
{
    QPushButton *pressed=(QPushButton *)sender();
    int pos=pressed->property("sh").toInt();
    QString info=lines[pos].info_to_html();
    QMessageBox::information(this,"INFO OF LINE "+QString::number(pos),info);
}
