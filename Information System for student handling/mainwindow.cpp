#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
   this->setFixedSize(900,900);
   this->setWindowTitle("SCHOOL BASE");
   mw=new QWidget;
   mw->setFixedSize(this->width(),this->height());
   this->setCentralWidget(mw);
   ml=new QStackedLayout;
   mydb=new database("SCHOOLDB.db");
   mydb->insert_credentials();
   mw->setLayout(ml);
   makemenu();
   makelineedit();
   makelineedit2();
   maketab3();
}
//ΔΗΜΙΟΥΡΓΙΑ ΜΕΝΟΥ
void MainWindow::makemenu()
{
    QMenu *sm=new QMenu("ΜΑΘΗΤΗΣ");
    sm->addAction("ΕΠΙΛΟΓΗ");
    sm->addAction("ΕΙΣΑΓΩΓΗ");
    sm->addAction("ΕΓΓΡΑΦΗ");
    sm->addAction("ΑΝΑΖΗΤΗΣΗ");
    sm->addAction("ΔΙΑΓΡΑΦΗ");
    QMenu *lm=new QMenu("ΜΑΘΗΜΑ");
    lm->addAction("ΕΠΙΛΟΓΗ");
    lm->addAction("ΝΕΟ ΜΑΘΗΜΑ");
    lm->addAction("ΑΠΟΔΟΣΗ ΜΑΘΗΜΑΤΟΣ");
    lm->addAction("ΔΙΑΓΡΑΦΗ");
    QMenu *tm=new QMenu("ΚΑΘΗΓΗΤΗΣ");
    tm->addAction("ΒΑΘΜΟΙ");
    menuBar()->addMenu(sm);
    menuBar()->addMenu(lm);
    menuBar()->addMenu(tm);
    connect(sm,SIGNAL(triggered(QAction *)),this,SLOT(stmenu(QAction *)));
    connect(lm,SIGNAL(triggered(QAction *)),this,SLOT(lsmenu(QAction *)));
    connect(tm,SIGNAL(triggered(QAction *)),this,SLOT(teachersslot(QAction *)));
}
//ΚΑΡΤΕΛΑ ΦΟΙΤΗΤΗ
void MainWindow::makelineedit()
{
    QWidget *tabwd=new QWidget;
    tabwd->setFixedSize(this->width(),this->height());
    ml->addWidget(tabwd);
    QVBoxLayout *ly=new QVBoxLayout;
    tabwd->setLayout(ly);
    QHBoxLayout *r1=new QHBoxLayout;
    QLabel *studentlabel=new QLabel;
    studentlabel->setText("<h2><p style=color:MidnightBlue;>ΚΑΡΤΕΛΑ ΜΑΘΗΤΗ</p></h2>");
    studentlabel->setStyleSheet("background-color:red;");
    studentlabel->setAlignment(Qt::AlignCenter);
    studentlabel->setFixedSize(0.98 *this->width(),0.1 * this->height());
    ly->addWidget(studentlabel);
    QLabel *l1=new QLabel;
    l1->setFixedSize(0.98 * this->width(),0.5*this->height());
    QPixmap pix(":/final.png");
    l1->setAlignment(Qt::AlignTop);
    l1->setStyleSheet("background-color:red;");
    l1->setStyleSheet("border:2px solid;");
    l1->setPixmap(pix.scaled(l1->size()));
    ly->addWidget(l1);
    ly->addLayout(r1);
    QLabel *info=new QLabel;
    info->setText("<h3><p style=color:blue>ADD STUDENT</h3></p>");
    i=new QLineEdit;
    i->setPlaceholderText("STUDENTS ID");
    i->setValidator(new QIntValidator(100,19000));
    ns=new QLineEdit;
    ns->setPlaceholderText("STUDENTS NAME");
    sem=new QLineEdit;
    sem->setPlaceholderText("STUDENTS SEMESTER");
    sem->setValidator(new QIntValidator(1,16));
    r1->addWidget(info);
    r1->addWidget(i);
    r1->addWidget(ns);
    r1->addWidget(sem);
    QHBoxLayout *r2=new QHBoxLayout;
    ly->addLayout(r2);
    QLabel *l2=new QLabel;
    l2->setText("<p style=color:blue><h3>ENROLL BLANK</h3></p>");
    l2->setAlignment(Qt::AlignVCenter);
    enid=new QComboBox;
    enid->setFixedWidth(0.46*this->width());
    enid->setEditable(true);
    enid->addItems(mydb->getstudents());
    enid->setValidator(new QIntValidator(100,19000));
    av_les=new QComboBox;
    av_les->setFixedWidth(0.36*this->width());
    av_les->setEditable(true);
    av_les->setStyleSheet("background-color:Tan;");
    av_les->addItems(mydb->getavailablelessons());
    r2->addWidget(l2);
    r2->addWidget(enid);
    r2->addWidget(av_les);
    QGridLayout *r4=new QGridLayout;
    ly->addLayout(r4);
    QLabel *l4=new QLabel;
    l4->setText("<p style=color:blue><h3>SEARCH AREA</h3></p>");
    sid=new QLineEdit;
    sid->setPlaceholderText("ID FOR SEARCH");
    sid->setValidator(new QIntValidator(100,22000));
    r4->addWidget(l4,0,0);
    r4->addWidget(sid,0,1);
    tab=new QTableWidget;
    QStringList l;
    l<<"LESSON"<<"GRADE";
    tab->setColumnCount(l.size());
    tab->setFixedSize(0.98 * this->width(),0.2 * this->height());
    tab->setHorizontalHeaderLabels(l);
    tab->setFixedSize(this->width()*0.98,0.20*this->height());
    ly->addWidget(tab);
}
//ΚΑΡΤΕΛΑ ΜΑΘΗΜΑΤΟΣ
void MainWindow::makelineedit2()
{
    QWidget *tabwg=new QWidget;
    tabwg->setFixedSize(this->width(),this->height());
    ml->addWidget(tabwg);
    QVBoxLayout *lay=new QVBoxLayout;
    tabwg->setLayout(lay);
    QLabel *lessonlabel=new QLabel;
    lessonlabel->setText("ΚΑΡΤΕΛΑ ΜΑΘΗΜΑΤΟΣ");
    lessonlabel->setStyleSheet("background-color:red;");
    lessonlabel->setAlignment(Qt::AlignCenter);
    lessonlabel->setFixedSize(0.98 *this->width(),0.1 * this->height());
    lay->addWidget(lessonlabel);
    QLabel *lb=new QLabel;
    lb->setFixedSize(this->width()*0.98,0.4*this->height());
    QPixmap pix(":/lessonnew.png");
    lb->setPixmap(pix.scaled(lb->size()));
    lb->setStyleSheet("border : 1px solid;");
    lay->addWidget(lb);
     QHBoxLayout *r=new QHBoxLayout;
    lay->addLayout(r);
    QLabel *l=new QLabel;
    l->setText("<p style=color:blue>ADD LESSON</p>");
    ln=new QLineEdit;
    ln->setPlaceholderText("LESSON NAME");
    lsem=new QLineEdit;
    lsem->setPlaceholderText("LESSONS SEMESTER");
    lsem->setValidator(new QIntValidator(1,8));
    QLabel *infolabel=new QLabel;
    infolabel->setText("<p style=color:blue>LESSON PERFORMANCE</p>");
    infolabel->setAlignment(Qt::AlignLeft);
    performance=new QComboBox;
    performance->addItems(mydb->getenrolledlessons());
    performance->setFixedWidth(0.44 * this->width());
    performance->setEditable(true);
    r->addWidget(l);
    r->addWidget(ln);
    r->addWidget(lsem);
    QHBoxLayout *r2=new QHBoxLayout;
    lay->addLayout(r2);
    r2->addWidget(infolabel);
    r2->addWidget(performance);
    ltab=new QTableWidget;
    ltab->setFixedSize(0.98 * this->width(),0.2 * this->height());
    QStringList ls;
    ls<<"ID"<<"GRADE";
    ltab->setColumnCount(ls.size());
    ltab->setHorizontalHeaderLabels(ls);
    lay->addWidget(ltab);
}
//ΚΑΡΤΕΛΑ ΚΑΘΗΓΗΤΗ
void MainWindow::maketab3()
{
    QWidget *w3=new QWidget;
    w3->setFixedSize(this->width(),this->height());
    ml->addWidget(w3);
    w3->setWindowTitle("GRADE UPDATE");
    QVBoxLayout *vb=new QVBoxLayout;
    w3->setLayout(vb);
    QLabel *in=new QLabel;
    in->setText("<p style=color:red>CHOOSE LESSON</p>");
    in->setStyleSheet("background-color:DarkSlateGrey;");
    lesn=new QComboBox;
    lesn->setEditable(true);
    lesn->addItems(mydb->getenrolledlessons());
    QPushButton *src=new QPushButton;
    src->setText("SEARCH");
    QHBoxLayout *row1=new QHBoxLayout;
    vb->addLayout(row1);
    row1->addWidget(in);
    row1->addWidget(lesn);
    row1->addWidget(src);
    connect(src,SIGNAL(clicked(bool)),this,SLOT(updatetable()));
    grades=new QTableWidget;
    QStringList lst;
    lst<<"ID"<<"GRADE";
    grades->setColumnCount(lst.size());
    grades->setHorizontalHeaderLabels(lst);
    grades->setFixedSize(this->width()*0.98,0.70*this->height());
    vb->addWidget(grades);
    QPushButton *push=new QPushButton;
    push->setText("SUBMIT");
    push->setStyleSheet("background-color:Lime;");
    push->setFixedWidth(0.27 * this->width());
    QGridLayout *grid=new QGridLayout;
    vb->addLayout(grid);
    grid->addWidget(push,0,0);
    connect(push,SIGNAL(clicked(bool)),this,SLOT(submitslot()));
}
MainWindow::~MainWindow() {delete mydb;}
void MainWindow::stmenu(QAction *ac)
{
    //ΕΠΙΛΟΓΗ ΜΕΝΟΥ ΜΑΘΗΤΩΝ
    if(ac->text()=="ΕΠΙΛΟΓΗ")
    {
        ml->setCurrentIndex(0);
    }
    //ΕΙΣΑΓΩΓΗ ΦΟΙΤΗΤΗ
    else if(ac->text()=="ΕΙΣΑΓΩΓΗ")
    {
        if(mydb->is_in(i->text().toInt()))
        {
            QMessageBox::warning(this,"INFO","<p style=color:green>Student already enrolled in database</p>");
            return;
        }
        if(i->text().isEmpty() || ns->text().isEmpty() || sem->text().isEmpty())
        {
            QMessageBox::critical(this,"ERROR","<b>Fill all the blanks in STUDENTS BLANK</b>");
            return;
        }
        student s(i->text().toInt(),ns->text(),sem->text().toInt());
        enid->addItem(i->text()+"-"+ns->text());
        mydb->insert_student(s);
    }
    //ΕΙΣΑΓΩΓΗ ΣΤΟ ΜΑΘΗΜΑ,ΦΟΙΤΗΤΗ
    else if(ac->text()=="ΕΓΓΡΑΦΗ")
    {
        QString enrolltext=enid->currentText();
        QStringList enrollid=enrolltext.split("-");
        int decodeid=enrollid[0].toInt();
        if(mydb->already_enroll(av_les->currentText(),decodeid))
        {
            QMessageBox::critical(this,"ERROR","Student already enrolled in this lesson");
            return;
        }
        mydb->insert_enroll(decodeid,av_les->currentText());
        lesn->clear();
        performance->clear();
        lesn->addItems(mydb->getenrolledlessons());
        performance->addItems(mydb->getenrolledlessons());
    }
    else if(ac->text()=="ΑΝΑΖΗΤΗΣΗ")
    {
        if(sid->text().isEmpty())
        {
            QMessageBox::critical(this,"ERROR","<b>Fill all the blanks in STUDENTS BLANK</b>");
            return;
        }
        else if(!mydb->is_in(sid->text().toInt()))
        {
            QMessageBox::critical(this,"ERROR","NO STUDENT WITH THIS ID FOUND AT DATABASE");
            return;
        }
        QVector<resultsperid> grades=mydb->findstudent(sid->text().toInt());
        tab->setRowCount(grades.size());
        tab->clearContents();
        for(int i=0;i<tab->rowCount();i++)
        {
            tab->setItem(i,0,new QTableWidgetItem(grades.at(i).ln));
            tab->setItem(i,1,new QTableWidgetItem(QString::number(grades.at(i).grade)));
        }
    }
    else
    {
        int id=QInputDialog::getInt(this,"ID BLANK","<p style=color:red>Give id you want to delete</p>",i->text().toInt(),100,22000);
        if(mydb->delete_student(id))
        QMessageBox::information(this,"SUCCESS","<b>Student "+QString::number(id)+" has been deleted from database</b>");
        else
        {
            QMessageBox::critical(this,"Warning","No student with id:"+QString::number(id)+"found");
            return;
        }
        enid->clear();
        enid->addItems(mydb->getstudents());
        lesn->clear();
        performance->clear();
        lesn->addItems(mydb->getenrolledlessons());
        performance->addItems(mydb->getenrolledlessons());
    }
}
void MainWindow::lsmenu(QAction *a)
{
    //ΕΠΙΛΟΓΗ ΜΕΝΟΥ ΜΑΘΗΜΑΤΩΝ
    if(a->text()=="ΕΠΙΛΟΓΗ")
    {
        ml->setCurrentIndex(1);
    }
    //ΝΕΟ ΜΑΘΗΜΑ
    else if(a->text()=="ΝΕΟ ΜΑΘΗΜΑ")
    {
        if(ln->text().isEmpty() || lsem->text().isEmpty() )
        {
            QMessageBox::critical(this,"ERROR","Fill all the blanks in LESSONS BLANK");
            return;
        }
        if(mydb->lesson_is_in(ln->text()))
        {
            QMessageBox::critical(this,"ERROR","Lesson already exists in database");
            return;
        }
        lesson l(ln->text(),lsem->text().toInt());
        mydb->insert_lesson(l);
        av_les->addItem(ln->text());
    }
    //ΑΠΟΔΟΣΗ ΣΕ ΕΝΑ ΜΑΘΗΜΑ
    else if(a->text()=="ΑΠΟΔΟΣΗ ΜΑΘΗΜΑΤΟΣ")
    {
       //QString les=QInputDialog::getText(this,"Give lesson name","please enter lesson name you want to search in order to find performance in lesson:");
       QVector <results> res=mydb->lesson_performance(performance->currentText());
       if(res.size()==0)
       {
           QMessageBox::critical(this,"ERROR","No lesson found or no student enroll to this lesson");
           return;
       }
       ltab->setRowCount(res.size());
       for(int i=0;i<ltab->rowCount();i++)
       {
           ltab->setItem(i,0,new QTableWidgetItem(QString::number(res.at(i).am)));
           ltab->setItem(i,1,new QTableWidgetItem(QString::number(res.at(i).grade)));
       }
    }
    else
    {
        QString les=QInputDialog::getText(this,"Give lesson name","Give lessonname you want to delete:");
        if(!mydb->delete_lesson(les))
        {
             QMessageBox::information(this,"DELETE LESSON","Lesson:"+les+" has been deleted from database");
             av_les->clear();
             av_les->addItems(mydb->getavailablelessons());
             lesn->clear();
             performance->clear();
             lesn->addItems(mydb->getenrolledlessons());
             performance->addItems(mydb->getenrolledlessons());
        }
        else
         {
            QMessageBox::information(this,"DELETE LESSON","Lesson:"+les+" has not been deleted from database or has not found in database");
          }
    }
}
//ΑΝΑΝΕΩΣΗ ΠΙΝΑΚΑ ΜΕ ΜΑΘΗΤΕΣ ΓΙΑ ΕΝΑ ΕΠΙΛΕΓΜΕΝΟ ΜΑΘΗΜΑ
void MainWindow::updatetable()
{
    QVector <results> res=mydb->lesson_performance(lesn->currentText());
    grades->setRowCount(res.size());
    for(int i=0;i<grades->rowCount();i++)
    {
        QLineEdit *id=new QLineEdit;
        id->setText(QString::number(res[i].am));
        id->setEnabled(false);
        grades->setCellWidget(i,0,id);
        QLineEdit *gr=new QLineEdit;
        gr->setText(QString::number(res[i].grade));
        grades->setCellWidget(i,1,gr);
    }
}
//ΕΙΣΑΓΩΓΗ ΒΑΘΜΩΝ
void  MainWindow::submitslot()
{
   for(int i=0;i<grades->rowCount();i++)
   {
       QLineEdit *temp=(QLineEdit *)grades->cellWidget(i,0);
       QLineEdit *vathmos=(QLineEdit *)grades->cellWidget(i,1);
       mydb->update_grade(temp->text().toInt(),lesn->currentText(),vathmos->text().toDouble());
   }
}
//ΚΑΡΤΕΛΑ TEACHER(ΜΕΤΑΒΑΣΗ)
void MainWindow::teachersslot(QAction *ta)
{
    if(ta->text()=="ΒΑΘΜΟΙ")
    {
        dialog d(*mydb);
        d.exec();
        if(d.enablecancelbutton()) return;
        while(d.exec()==QDialog::Rejected)
        {
            QMessageBox::critical(this,"ERROR","<p style=color:Maroon>Λάθος όνομα χρήστη η κωδικός παρακαλώ προσπαθήστε ξανά</p>");
              d.exec();

        }
        ml->setCurrentIndex(2);
    }
}

