#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QSlider>
#include <QLCDNumber>
#include <QDesktopWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMovie>
#include <QMediaPlayer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *lay;
    QTableWidget *tab;
    QMediaPlayer *player;
    QPushButton *showvolume;
    int lastvolume=10;
    QSlider *volume;
    QSlider *dur;
    QLabel *label,*volabel;
    QLCDNumber *counter;
    QPushButton *previous;
    bool muted=false;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void playslot();
    void pauseslot();
    void selectedslot();
    void volumeslot(int vol);
    void mutedslot();
    void poschanged(qint64 position);
    void moveslider(int position);
    void newduration(qint64 dr);
};
#endif // MAINWINDOW_H
