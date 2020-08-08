#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
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
    QLabel *label;
    QPushButton *previous;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void playslot();
};
#endif // MAINWINDOW_H
