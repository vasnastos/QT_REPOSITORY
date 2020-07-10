#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(600,800);
    this->setWindowTitle("Birth and Death app");
    QIcon ic(":/db.png");
    this->setWindowIcon(ic);
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    QLabel *lab=new QLabel;
    lab->setFixedWidth(0.96 * width());
    lab->setFixedHeight(0.4 * height());
    QPixmap px(":/icon.png");
    lab->setPixmap(px.scaled(lab->width(),lab->height()));
    lab->setStyleSheet("border:2px solid;");
    ml->addWidget(lab);
    p=new QLineEdit;
    p->setPlaceholderText("Give period");
    tp=new QLineEdit;
    tp->setPlaceholderText("GIVE TYPE");
    r=new QLineEdit;
    r->setPlaceholderText("Give region");
    c=new QLineEdit;
    c->setPlaceholderText("Count");
    QHBoxLayout *r1=new QHBoxLayout;
    ml->addLayout(r1);
    r1->addWidget(p);
    r1->addWidget(tp);
    r1->addWidget(r);
    r1->addWidget(c);
    QPushButton *b1=new QPushButton;
    b1->setText("ADD");
    QPushButton *b2=new QPushButton;
    b2->setText("SAVE");
    QHBoxLayout *r2=new QHBoxLayout;
    ml->addLayout(r2);
    r2->addWidget(b1);
    r2->addWidget(b2);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(addslot()));
    connect(b2,SIGNAL(clicked(bool)),this,SLOT(saveslot()));
    chart=new QChart();
    chart->setTitle("Live Statistics");
    srs=new QPieSeries;
    chart->addSeries(srs);
    vw=new QChartView(chart);
    vw->setFixedWidth(0.95 * width());
    tab=new QTableWidget;
    QStringList headers;
    headers<<"PERIOD"<<"TYPE"<<"REGION"<<"SUMMARY";
    tab->setColumnCount(headers.size());
    tab->setHorizontalHeaderLabels(headers);
    tab->setFixedWidth(0.95 * width());
    tab->setFixedHeight(0.2 * height());
    ml->addWidget(tab);
    vw->setWhatsThis("PieChart for total count of deaths and births");
    vw->setStyleSheet("border:2px solid;");
    vw->setRenderHint(QPainter::Antialiasing);
    ml->addWidget(vw);
    connect(this,SIGNAL(recordadd()),this,SLOT(addemit()));
}

MainWindow::~MainWindow() {}

void MainWindow::addslot()
{
    if(p->text().isEmpty() || tp->text().isEmpty() || r->text().isEmpty() || c->text().isEmpty())
    {
        QMessageBox::critical(this,"ERROR","Fill all the blanks");
        return;
    }
    for(auto &x:records)
    {
        if(x.get_type()==tp->text() && x.get_period()==p->text().toInt() && x.get_region()==r->text() && x.get_count()==c->text().toInt())
        {
            QMessageBox::critical(this,"ERROR","Record already exists");
            return;
        }
        else if(x.get_type()==tp->text() && x.get_period()==p->text().toInt() && x.get_region()==r->text())
        {
            x.setCount(c->text().toInt());
            return;
        }
    }
    record rd(p->text().toInt(),tp->text(),r->text(),c->text().toInt());
    records<<rd;
    emit addemit();
}

void MainWindow::addemit()
{
  tab->setRowCount(records.size());
  for(int i=0;i<tab->rowCount();i++)
  {
      tab->setItem(i,0,new QTableWidgetItem(QString::number(records[i].get_period())));
      tab->setItem(i,1,new QTableWidgetItem(records[i].get_type()));
      tab->setItem(i,2,new QTableWidgetItem(records[i].get_region()));
      tab->setItem(i,3,new QTableWidgetItem(QString::number(records[i].get_count())));
  }
  srs->clear();
  chart->removeSeries(srs);
  int cntb=0;
  int cntd=0;
  for(auto &x:records)
  {
      if(x.get_type()=="Births")
      {
          cntb++;
      }
      if(x.get_type()=="Deaths")
      {
          cntd++;
      }
  }
  srs->append("Births",cntb);
  srs->append("Deaths",cntd);
  chart->addSeries(srs);
}

void MainWindow::saveslot()
{
    QString fn=QFileDialog::getSaveFileName(this,"Save file",".","csv file (*.csv)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No file selected");
        return;
    }
    QFile fp(fn);
    bool ok=fp.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!ok) return;
    QTextStream st(&fp);
    for(auto &x:records)
    {
        st<<x.to_str()<<endl;
    }
    fp.close();
    QString img=QFileDialog::getSaveFileName(this,"Save image",".","png files (*.png)");
    if(img.size()==0) return;
    QPixmap pix=vw->grab();
    pix.save(img,"png");
}
