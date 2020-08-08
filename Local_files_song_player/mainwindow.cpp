#include "mainwindow.h"
#include <QDir>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
   QDesktopWidget *widg=new QDesktopWidget;
    this->setFixedSize(widg->geometry().width()/2,widg->geometry().height()/2);
    this->setWindowTitle("Multimedia test");
    mw=new QWidget;
    mw->setFixedSize(width(),height());
    this->setCentralWidget(mw);
    lay=new QVBoxLayout;
    mw->setLayout(lay);
    label=new QLabel;
    label->setFixedSize(0.95*width(),0.6*height());
    label->setStyleSheet("border:2px solid;");
    QMovie *movie=new QMovie;
    QSize size(label->width(),label->height());
    movie->setScaledSize(size);
    movie->setFileName(":/music.gif");
    label->setMovie(movie);
    lay->addWidget(label);
    tab=new QTableWidget;
    QStringList list;
    list<<"Title"<<"Action";
    tab->setColumnCount(list.size());
    tab->setHorizontalHeaderLabels(list);
    tab->setRowCount(3);
    QStringList header;
    for(int i=1;i<=3;i++)
    {
      header<<"Song_"+QString::number(i);
    }
    tab->setVerticalHeaderLabels(header);
    tab->setFixedSize(0.95*width(),0.3*height());
    QStringList songs;
    songs<<"Primo"<<"River"<<"Και εγώ σ'αγαπώ";
    for(int i=0;i<tab->columnCount();i++)
    {
        tab->setColumnWidth(i,tab->width()*0.98/tab->columnCount());
    }
    QTableWidgetItem it;
    for(int i=0;i<3;i++)
    {
        QTableWidgetItem *it=new QTableWidgetItem;
        it->setTextAlignment(1);
        it->setText(songs.at(i));
       tab->setItem(i,0,it);
       QPushButton *b=new QPushButton("Play");
       b->setProperty("song",i);
       b->setStyleSheet("padding: 3px 5px;"
                        "font-size: 20px;"
                        "text-align: center;"
                        "color: #c95165;"
                        "background-color: #0a1338;"
                        "border: none;"
                        "border-radius: 15px;");
       b->setFixedWidth(0.5*this->width());
       tab->setCellWidget(i,1,b);
       connect(b,SIGNAL(clicked(bool)),this,SLOT(playslot()));
    }
    tab->setStyleSheet("border:2px solid;");
    lay->addWidget(tab);
    player=new QMediaPlayer;
}

MainWindow::~MainWindow()
{
}

void MainWindow::playslot()
{
    QPushButton *click=(QPushButton *)sender();
    int pos=click->property("song").toInt();
    if(pos==0)
    {

        player->setMedia(QUrl("qrc:/primo.mp3"));
        if(click->text()=="Play")
        {
            QMovie *m=new QMovie;
            QSize size(label->width(),label->height());
            m->setScaledSize(size);
            m->setFileName(":/light.gif");
            label->setMovie(m);
            label->movie()->start();
            player->setVolume(50);
            player->play();
            click->setText("Pause");
        }
        else if(click->text()=="Pause")
        {
            label->movie()->stop();
            player->pause();
            click->setText("Play");
        }
    }
    if(pos==1)
    {

        player->setMedia(QUrl("qrc:/River.mp3"));
        if(click->text()=="Play")
        {
            QMovie *m=new QMovie;
            QSize size(label->width(),label->height());
            m->setScaledSize(size);
            m->setFileName(":/river.gif");
            label->setMovie(m);
            label->movie()->start();
            player->setVolume(50);
            player->play();
            click->setText("Pause");
        }
        else if(click->text()=="Pause")
        {
            label->movie()->stop();
            player->pause();
            click->setText("Play");
        }
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
        if(click->text()=="Play")
        {
            player->setVolume(50);
            player->play();
            click->setText("Pause");
        }
        else if(click->text()=="Pause")
        {
            label->movie()->stop();
            player->pause();
            click->setText("Play");
        }
    }
}
