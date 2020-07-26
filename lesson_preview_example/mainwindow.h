#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QApplication>
#include <QMenu>
#include "dialog.h"
#include <QMenuBar>
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QIcon>
#include "database.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QDesktopWidget>

using namespace QtCharts;

struct student
{
    int id;
    double gradetheory;
    double gradelab;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QString lesson="";
    double precenttheory,precentlab;
    QTableWidget *tab;
    void make_menu();
    bool loadedfromdb;
    QChart *chart;
    QPieSeries *series;
    database *mydb;
    QChartView *view;
    QVector <student> students;
    QVector <dets> loadeddetails;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void menuslot(QAction *a);
    void showfinal();
    void menuslot1(QAction *a);
};
#endif // MAINWINDOW_H
