#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMediaContent>
#include <QMediaPlaylist>
#include <QSlider>
#include <QLCDNumber>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStackedLayout>
#include <QMovie>
#include <QMediaPlayer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QStackedLayout *ml;
    QVBoxLayout *lay;
    QTableWidget *tab;
    QMediaPlayer *player;
    QPushButton *showvolume;
    void window1();
    void window2();
    QMediaPlaylist *playlist;
    int lastvolume=10;
    QSlider *volume;
    QPushButton *play;
    QSlider *dur;
    QLabel *preview;
    bool enableplaylist=false;
    bool ispause=false;
    void make_menu();
    QLabel *label,*volabel;
    QStringList loadsinger;
    QLCDNumber *counter;
    QPushButton *previous;
    QStringList localfiles;
    QStringList songs;
    QStringList singer;
    QPushButton *toggle,*nextsong;
    bool muted=false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void playslot();
    void selectedslot();
    void volumeslot(int vol);
    void mutedslot();
    void poschanged(qint64 position);
    void moveslider(int position);
    void newduration(qint64 dr);
    void menuslot(QAction *ac);
    void shuffleslot();
    void nextsongslot();
    //void songchanged(int index);
};
#endif // MAINWINDOW_H
