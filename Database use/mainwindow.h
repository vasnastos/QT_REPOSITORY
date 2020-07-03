#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>
#include <QLineEdit>
#include "database.h"
#include <QFile>
#include <QVector>
#include <QPushButton>
#include <QMenu>
#include <QLabel>
#include <QMessageBox>
#include <QMenuBar>
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidget>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QStackedLayout *ml;
    database *mydb;
    QTableWidget *tab;
    QLineEdit *s;
    QMenu *fn;
    QLabel *label,*lab1;
    void makemenu();
    void tab1();
    void tab2();
    void tab3();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void load();
    void save();
    void search();
    //void getaverage();
    void tabsl(QAction *a);
};
#endif // MAINWINDOW_H
