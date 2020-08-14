#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QVideoWidget *video;
    QLabel *songlabel;
    QSlider *volume;
    QMediaPlayer *player;
    int lastvolume=0;
    QLabel *vol;
     QLabel *lb;
     QLabel *durlb;
     QSlider *dur;
     bool paused=false;
     QPushButton *p;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void newvalue(int val);
    void playpauseslot();
    void poschanged(qint64 newpos);
    void moveslider(int newpos);
    void newduration(qint64 duration);
};
#endif // MAINWINDOW_H
