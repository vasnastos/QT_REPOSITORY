#include "mainwindow.h"
#include <QDir>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   QDesktopWidget *widg=new QDesktopWidget;
    this->setFixedSize(widg->geometry().width()/2,widg->geometry().height()/2);
    this->setWindowTitle("Music Player");
    this->setWindowIcon(QIcon(":/music.png"));
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    lay=new QVBoxLayout;
    mw->setLayout(lay);
    label=new QLabel;
    label->setFixedSize(0.95*width(),0.5*height());
    label->setStyleSheet("border:2px solid;");
    QMovie *movie=new QMovie;
    QSize size(label->width(),label->height());
    movie->setScaledSize(size);
    movie->setFileName(":/music.gif");
    label->setMovie(movie);
    lay->addWidget(label);
    tab=new QTableWidget;
    QStringList list;
    list<<"TITLE"<<"SIGNER"<<"ACTION";
    tab->setColumnCount(list.size());
    tab->setHorizontalHeaderLabels(list);
    tab->setFixedSize(0.95*width(),0.3*height());
    QStringList songs;
    songs<<"Primo"<<"River"<<"Και εγώ σ'αγαπώ"<<"Caliente";
    QStringList singer;
    singer<<"Light"<<"Eminem ft Sheeran"<<"Pantelidis"<<"Mente Fuerte,Hawk,Baghdad";
    tab->setColumnWidth(0,0.3*tab->width());
    tab->setColumnWidth(1,tab->width()*0.5);
    tab->setColumnWidth(2,tab->width()*0.2);
    tab->setRowCount(singer.size());
    QTableWidgetItem it;
    for(int i=0;i<tab->rowCount();i++)
    {
        QTableWidgetItem *it=new QTableWidgetItem;
        it->setText(songs.at(i));
       tab->setItem(i,0,it);
       tab->setItem(i,1,new QTableWidgetItem(singer[i]));
       QPushButton *b1=new QPushButton("SELECT");
       b1->setFixedWidth(0.18*tab->width());
       b1->setStyleSheet("padding: 2px 5px;"
                         "font-size: 18px;"
                         "text-align: center;"
                         "color: #c95165;"
                         "background-color: #0a1338;"
                         "border: none;"
                         "border-radius: 10px;");
       b1->setProperty("song",i);
       tab->setCellWidget(i,2,b1);
       connect(b1,SIGNAL(clicked(bool)),this,SLOT(selectedslot()));
    }
    tab->setStyleSheet("border:1px solid;");
    lay->addWidget(tab);
    dur=new QSlider(Qt::Horizontal);
    dur->setTickPosition(QSlider::TicksBothSides);
    dur->setMinimum(0);
    dur->setTickInterval(1);
    dur->setFixedWidth(0.95*width());
    counter=new QLCDNumber;
    counter->display(0.00);
    counter->setFixedWidth(0.08*width());
    counter->setFixedHeight(0.05*height());
    counter->setStyleSheet("border:2px solid;");
    lay->addWidget(dur);
    QPushButton *play=new QPushButton;
    play->setFixedWidth(0.05*width());
    play->setFixedHeight(0.05 * height());
    play->setIcon(QIcon(":/play.png"));
    play->setStyleSheet("background-color: #e6e6e6;");
    QSize sbut(play->width(),play->height());
    play->setIconSize(sbut);
    QPushButton *pause=new QPushButton;
    pause->setFixedWidth(0.05*width());
    pause->setFixedHeight(0.05 * height());
    pause->setIcon(QIcon(":/pause.png"));
    pause->setStyleSheet("background-color: #e6e6e6;");
    QSize sbut1(pause->width(),pause->height());
    pause->setIconSize(sbut1);
    showvolume=new QPushButton;
    showvolume->setFixedWidth(0.05*width());
    showvolume->setFixedHeight(0.05*height());
    showvolume->setIcon(QIcon(":/nm.png"));
    showvolume->setStyleSheet("background-color:#e6e6e6;");
    QSize butsize(showvolume->width(),showvolume->height());
    showvolume->setIconSize(butsize);
    player=new QMediaPlayer;
    volume=new QSlider(Qt::Horizontal);
    volume->setMaximum(100);
    volume->setMinimum(0);
    volume->setValue(0);
    volume->setTickInterval(1);
    volume->setFixedWidth(0.5*width());
    volabel=new QLabel;
    volabel->setFixedWidth(0.1*width());
    volabel->setAlignment(Qt::AlignLeading);
    volabel->setFixedHeight(0.05*height());
    volabel->setText("<b>Volume:0%</b>");
    QHBoxLayout *row=new QHBoxLayout;
    lay->addLayout(row);
    row->addWidget(play);
    row->addWidget(pause);
    row->addWidget(showvolume);
    row->addWidget(volume);
    row->addWidget(volabel);
    row->addWidget(counter);
    connect(volume,SIGNAL(valueChanged(int)),this,SLOT(volumeslot(int)));
    connect(showvolume,SIGNAL(clicked(bool)),this,SLOT(mutedslot()));
    connect(dur,SIGNAL(sliderMoved(int)),this,SLOT(moveslider(int)));
    connect(play,SIGNAL(clicked(bool)),this,SLOT(playslot()));
    connect(pause,SIGNAL(clicked(bool)),this,SLOT(pauseslot()));
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(poschanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(newduration(qint64)));
}

MainWindow::~MainWindow()
{
    qDebug()<<"Destructor called!!!"<<endl;
    qDebug()<<"Thank you for using the App!!!GoodBye***"<<endl;
}

void MainWindow::playslot()
{
   player->play();
}

void MainWindow::pauseslot()
{
    player->pause();
}

void MainWindow::selectedslot()
{
    QPushButton *click=(QPushButton *)sender();
    player->setVolume(lastvolume);
    volume->setValue(lastvolume);
    int pos=click->property("song").toInt();
    tab->selectRow(pos);
    if(pos==0)
    {

        player->setMedia(QUrl("qrc:/primo.mp3"));
         QMovie *m=new QMovie;
         QSize size(label->width(),label->height());
         m->setScaledSize(size);
         m->setFileName(":/light.gif");
         label->setMovie(m);
         label->movie()->start();
         player->play();
    }
    if(pos==1)
    {

        player->setMedia(QUrl("qrc:/River.mp3"));
        QMovie *m=new QMovie;
        QSize size(label->width(),label->height());
        m->setScaledSize(size);
        m->setFileName(":/river.gif");
        label->setMovie(m);
        label->movie()->start();
        player->play();
    }
    if(pos==2)
    {
        QMovie *m=new QMovie;
        QSize size(label->width(),label->height());
        m->setScaledSize(size);
        m->setFileName(":/music.gif");
        label->setMovie(m);
        label->movie()->start();       
        player->setMedia(QUrl("qrc:/love.mp3"));
        player->play();
    }
    if(pos==3)
    {
        label->setPixmap(QPixmap(":/caliente.png").scaled(label->width(),label->height()));
        player->setMedia(QUrl("qrc:/Caliente.mp3"));
        player->play();
    }
}

void MainWindow::volumeslot(int vol)
{
    player->setVolume(vol);
    lastvolume=vol;
    volabel->setText("<b>Volume:"+QString::number(vol)+"%</b>");
    if(muted)
    {
      showvolume->setIcon(QIcon(":/nm.png"));
    }
    else if(vol>=0 && vol<100/3)
    {
        showvolume->setIcon(QIcon(":/music1.png"));
    }
    else if(vol<2*(100/3))
    {
        showvolume->setIcon(QIcon(":/music2.png"));
    }
    else
    {
        showvolume->setIcon(QIcon(":/music3.png"));
    }
    QSize size(showvolume->width(),showvolume->height());
    showvolume->setIconSize(size);
}

void MainWindow::mutedslot()
{
    muted=!muted;
    if(muted)
    {
        showvolume->setIcon(QIcon(":/nm.png"));
        QSize size(showvolume->width(),showvolume->height());
        showvolume->setIconSize(size);
    }
    else
    {
       int value=volume->value();
       if(value>=0 && value<100/3)
       {
           showvolume->setIcon(QIcon(":/music1.png"));
       }
       else if(value<2*(100/3))
       {
           showvolume->setIcon(QIcon(":/music2.png"));
       }
       else
       {
           showvolume->setIcon(QIcon(":/music3.png"));
       }
       QSize size(showvolume->width(),showvolume->height());
       showvolume->setIconSize(size);
    }
    player->setMuted(muted);
}

void MainWindow::poschanged(qint64 position)
{
    double newposition=position/(1000.0*60.0);
    int value=newposition*100;
    if(value==0)
    {
        return;
    }
    counter->display(newposition);
    dur->setValue(value);
}

void MainWindow::moveslider(int position)
{
    double newposition=(double)position/100.0;
    counter->display(newposition);
    int playerposition=(newposition*60.0)*1000.0;
    player->setPosition(playerposition);
}

void MainWindow::newduration(qint64 dr)
{
    double maxval=(dr/(1000.0*60.0));
    int duration=maxval*100;
    dur->setMaximum(duration);
}
