#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QApplication>
#include <QStackedLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QKeyEvent>

struct calreg
{
    QString time;
    QString prg;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QStackedLayout *lay;
    QLabel *res;
    QToolBar *bar;
    void window1();
    void make_menu();
    void window2();
    void panel1();
    void panel2();
    void panel3();
    void panel4();
    void panel5();
    QVector <calreg> prks;
    QTableWidget *tab;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *k);
signals:
    void calculation();
public slots:
    void backspaceslot();
    void parenthesis1();
    void parenthesis2();
    void xslot();
    void panel2slot();
    void divslot();
    void plusslot();
    void minusslot();
    void dotslot();
    void eslot();
    void dynslot();
    void clearslot();
    void modslot();
    void sqrtslot();
    void pislot();
    void menuslot(QAction *a);
    void calcslot();
    void exportcsv();
    void resultslot();
    void newcalc();
};
#endif // MAINWINDOW_H
