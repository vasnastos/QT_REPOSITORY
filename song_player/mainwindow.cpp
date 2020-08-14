#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
      player=new QMediaPlayer;
    this->setFixedSize(500,500);
    this->setWindowTitle("Video Player");
    mw=new QWidget;
    mw->setFixedSize(this->width(),this->height());
    this->setCentralWidget(mw);
    ml=new QVBoxLayout;
    mw->setLayout(ml);
    lb=new QLabel;
    lb->setFixedSize(0.4*this->width(),0.2*this->height());
    lb->setAlignment(Qt::AlignCenter);
    lb->setText("Load Song");
    QPushButton *b1=new QPushButton("Load");
    b1->setStyleSheet("padding: 2px 5px;"
                      "font-size: 19px;"
                      "text-align: center;"
                      "color: #b30046;"
                      "background-color: #e6ffff;"
                      "border: 1px solid black;"
                      "border-radius: 2px solid black;"
                      "font-weight: bold;");
    b1->setFixedWidth(0.4*width());
    QHBoxLayout *row1=new QHBoxLayout;
    ml->addLayout(row1);
    row1->addWidget(lb);
    row1->addWidget(b1);
    video=new QVideoWidget;
    video->setFixedSize(0.95*this->width(),0.4*this->height());
    video->setStyleSheet("border:2px solid;");
    ml->addWidget(video);
    p=new QPushButton;
    p->setStyleSheet("background-color: #f1f1f1;"
                     "border: none;"
                     "color: white;"
                     "padding: 35px 32px;"
                     "text-align: center;"
                     "text-decoration: none;"
                     "font-size: 26px;"
                     "margin: 4px 2px;"
                     );
    p->setFixedWidth(0.05*width());
    p->setFixedHeight(0.05*height());
    p->setIcon(QIcon(":/play.png"));
    QSize size(p->width(),p->height());
    p->setIconSize(size);
    QHBoxLayout *row3=new QHBoxLayout;
    ml->addLayout(row3);
    dur=new QSlider(Qt::Horizontal);
    dur->setFixedWidth(0.70*width());
    dur->setStyleSheet("border: 1px solid #999999;"
                       "height: 1px solid; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */"
                       "color:blue;"
                       "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 black, stop:1 black);"
                       "margin: 3px;");
    dur->setMinimum(0);
    dur->setTickInterval(1);
    dur->setVisible(false);
    durlb=new QLabel;
    durlb->setFixedSize(0.2*width(),0.05*height());
    durlb->setAlignment(Qt::AlignCenter);
    durlb->setText("<p style=color:red>0.00</p>");
    durlb->setVisible(false);
    row3->addWidget(dur);
    row3->addWidget(durlb);
    volume=new QSlider(Qt::Horizontal);
    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setTickInterval(1);
    volume->setFixedWidth(0.6*width());
    volume->setValue(lastvolume);
    vol=new QLabel;
    vol->setFixedSize(0.15*width(),0.1*height());
    vol->setAlignment(Qt::AlignCenter);
    vol->setText("<b>Volume:0%</b>");
    QHBoxLayout *row2=new QHBoxLayout;
    ml->addLayout(row2);
    volume->setVisible(false);
    vol->setVisible(false);
    p->setVisible(false);
    row2->addWidget(p);
    row2->addWidget(volume);
    row2->addWidget(vol);
    connect(b1,SIGNAL(clicked(bool)),this,SLOT(loadslot()));
    connect(volume,SIGNAL(valueChanged(int)),this,SLOT(newvalue(int)));
    connect(p,SIGNAL(clicked(bool)),this,SLOT(playpauseslot()));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(poschanged(qint64)));
    connect(dur,SIGNAL(sliderMoved(int)),this,SLOT(moveslider(int)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(newduration(qint64)));
}

MainWindow::~MainWindow() {}

void MainWindow::loadslot()
{
    QString fn=QFileDialog::getOpenFileName(this,"Load song",".","song with video (*.mp4)");
    if(fn.size()==0)
    {
        QMessageBox::critical(this,"ERROR","No file selected");
        return;
    }
    volume->setVisible(true);
    vol->setVisible(true);
    p->setVisible(true);
    dur->setVisible(true);
    durlb->setVisible(true);
    player->setMedia(QUrl(fn));
    player->setVideoOutput(video);
    player->setVolume(10);
    volume->setValue(10);
    p->setIcon(QIcon(":/pause.png"));
    QSize size(p->width(),p->height());
    p->setIconSize(size);
    player->play();
    QStringList list=fn.split("/");
    lb->setText("<p style=color:red>"+list[list.size()-1]+"</p>");
}

void MainWindow::newvalue(int val)
{
    player->setVolume(val);
    lastvolume=val;
    vol->setText("<b>Volume:"+QString::number(val)+"%</b>");
}

void MainWindow::playpauseslot()
{
    paused=!paused;
   if(paused)
   {
       p->setIcon(QIcon(":/play.png"));
       QSize size(p->width(),p->height());
       p->setIconSize(size);
       player->pause();
   }
   else
   {
       p->setIcon(QIcon(":/pause.png"));
       QSize size(p->width(),p->height());
       p->setIconSize(size);
       player->play();
       qDebug()<<player->duration();
   }
}

void MainWindow::poschanged(qint64 newpos)
{
   double currentpos=newpos/(60.0*1000.0);
   int mainpos=currentpos*100.0;
   dur->setValue(mainpos);
   durlb->setText("<p style=color:red>"+QString::number(currentpos,'f',2)+"</p>");
}

void MainWindow::moveslider(int newpos)
{
    double playerpos=(double)newpos/100;
    playerpos*=60.0*1000.0;
    player->setPosition(playerpos);
    durlb->setText("<p style=color:red>"+QString::number(newpos/100.0,'f',2)+"</p>");
}

void MainWindow::newduration(qint64 duration)
{
    double total=(double)duration/(60*1000);
    int setduration=total*100;
    qDebug()<<setduration;
    dur->setMaximum(setduration);
}
