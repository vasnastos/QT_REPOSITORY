#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,600);
    this->setWindowTitle("CSV HANDLER");
    this->setWindowIcon(QIcon(":/csv.png"));
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lb=new QLabel;
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("<h3>Csv file Handling with Headers</h3>");
    lb->setFixedSize(0.95*width(),0.10*height());
    lb->setStyleSheet("background-color:#e6ff99;");
    ml->addWidget(lb);
    tab=new QTableWidget;
    tab->setFixedWidth(0.95*width());
    tab->setFixedHeight(0.50 * height());
    tab->setShowGrid(true);
    tab->setWhatsThis("<b>Preview of the csv</b>");
    ml->addWidget(tab);
    make_menu();
    mydb=new database;
    QPushButton *b=new QPushButton;
    b->setText("Upload");
    b->setStyleSheet( "padding: 2px 5px;"
                     "font-size: 20px;"
                     "text-align: center;"
                     "color: #fff;"
                     "background-color:#a83236;"
                     "border: none;"
                     "border-radius: 8px;");
    QPushButton *b1=new QPushButton("SAVE");
    b1->setStyleSheet("padding: 2px 5px;"
                      "font-size: 20px;"
                      "text-align: center;"
                      "color: #fff;"
                      "background-color:#a83236;"
                      "border: none;"
                      "border-radius: 8px;");
    QPushButton *b3=new QPushButton("DELETE");
    b3->setStyleSheet("padding: 2px 5px;"
                      "font-size: 20px;"
                      "text-align: center;"
                      "color: #fff;"
                      "background-color:#a83236;"
                      "border: none;"
                      "border-radius: 8px;");
    title=new QLineEdit;
    title->setPlaceholderText("Give title of file");
    title->setFixedWidth(0.3 * width());
    QLabel *in=new QLabel;
    in->setAlignment(Qt::AlignCenter);
    in->setFixedWidth(0.2*width());
    in->setFixedHeight(0.04*height());
    in->setFixedWidth(0.3 * width());
    in->setText("<h4>INSERT CSV</h4>");
    in->setStyleSheet("background-color:#3289a8;");
    b->setFixedWidth(0.3 * width());
    QHBoxLayout *r=new QHBoxLayout;
    ml->addLayout(r);
    r->addWidget(in);
    r->addWidget(title);
    r->addWidget(b);
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    titles=new QComboBox;
    titles->addItems(mydb->get_saved_files());
    titles->setFixedWidth(0.3 * width());
    b1->setFixedWidth(0.3 * width());
    b3->setFixedWidth(0.3 * width());
    r1->addWidget(titles);
    r1->addWidget(b1);
    r1->addWidget(b3);
    connect(b,SIGNAL(clicked(bool)),this,SLOT(uploadslot()));
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(saveslot()));
    connect(b3,SIGNAL(clicked(bool)),this,SLOT(deleteslot()));
}

void MainWindow::make_menu()
{
    QMenu *men=new QMenu;
    men->setIcon(QIcon(":/file.png"));
    men->setTitle("File");
    men->addAction(QIcon(":/upload.png"),"LOAD");
    men->addAction(QIcon(":/exit.png"),"QUIT");
    menuBar()->addMenu(men);
    connect(men,SIGNAL(triggered(QAction *)),this,SLOT(menuslot(QAction *)));
}

MainWindow::~MainWindow() {delete mydb;}

void MainWindow::menuslot(QAction *a)
{
    if(a->text()=="LOAD")
    {
        tab->clear();
      QString fn=QFileDialog::getOpenFileName(this,"Load csv",".","csv files (*.csv *.txt)");
      if(fn==0)
      {
          QMessageBox::critical(this,"Error","No file Selected");
          return;
      }
      QFile fp(fn);
      fp.open(QIODevice::ReadOnly);
      QTextStream st(&fp);
      int counter=0;
      QVector <QString> contains;
      while(!st.atEnd())
      {

         QString line=st.readLine();
         if(line.startsWith("#")) continue;
         if(line.size()==0) continue;
         counter++;
         if(counter==1)
         {
             QStringList commasplit=line.split(",");
             tab->setColumnCount(commasplit.size());
             for(int i=0;i<tab->columnCount();i++)
             {
                 tab->setColumnWidth(i,(0.9*tab->width())/tab->columnCount());
             }
            tab->setHorizontalHeaderLabels(commasplit);
         }
         else
         {
            contains.append(line);
         }
      }
      fp.close();
      tab->setRowCount(contains.size());
      int ck=0;
      for(auto &x:contains)
      {
         spl.clear();
         spl=x.split(",");
         if(spl.size()!=tab->columnCount())
         {
             qDebug()<<"Error data detecting!!!Skiping this line"<<endl;
             continue;
         }
         for(int i=0;i<spl.size();i++)
         {
             tab->setItem(ck,i,new QTableWidgetItem(spl[i]));
         }
         ck++;
       }
      }
      else if(a->text()=="QUIT")
      {
        qApp->exit(EXIT_SUCCESS);
      }
}
void MainWindow::uploadslot()
{
    if(title->text().isEmpty() || tab->rowCount()==0)
    {
        QMessageBox::critical(this,"Error","check the code of select a file");
        return;
    }
    QString date=__DATE__;
    QString time=__TIME__;
   QString file="#File uploaded at:"+date+"  "+time+"\n";
   file+="#Information about "+title->text()+"\n";
   file+="#    DATA\n";
   file+="\n";
   int i=0;
   for(auto &x:spl)
   {
      if(i<spl.size()-1)
       file+=x+",";
      else
          file+=x;
      i++;
   }
   file+="\n";
   for(int i=0;i<tab->rowCount();i++)
   {
       for(int j=0;j<tab->columnCount();j++)
       {
           if(j<tab->columnCount()-1)
           {
               file+=tab->item(i,j)->text()+",";
           }
           else
           {
               file+=tab->item(i,j)->text();
           }
       }
       file+="\n";
   }
   if(mydb->is_in(title->text()))
   {
       QMessageBox::critical(this,"ERROR","File with this name already exists please type a different name");
       QString t=title->text();
       QStringList sp=t.split("(");
       if(sp.size()==1)
       title->setText(t+"(2)");
       else
       {
           QString index="";
           index+=sp[1].at(0);
           int i=index.toInt();
           index=QString::number(i+1);
           title->setText(sp[0]+"("+index+")");
       }
       title->setStyleSheet("background-color:#15b4ed;");
       return;
   }
   mydb->insert_file(title->text(),file);
   titles->clear();
   title->setStyleSheet("background-color:white;");
   titles->addItems(mydb->get_saved_files());
}

void MainWindow::saveslot()
{
    QString fn=QFileDialog::getSaveFileName(this,"Save csv file",".","csv files (*.csv)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"Error","No file selected");
        return;
    }
    QFile out(fn);
    out.open(QIODevice::WriteOnly);
    QTextStream stream(&out);
    QString output=mydb->get_file_by_title(titles->currentText());
    stream<<output;
    out.close();
}

void MainWindow::deleteslot()
{
    QString deletetittle=titles->currentText();
    titles->clear();
    mydb->delete_record(deletetittle);
    titles->addItems(mydb->get_saved_files());
}
