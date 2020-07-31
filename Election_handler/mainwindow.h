#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QFile>
#include <QStackedLayout>
#include <QTextStream>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QFileDialog>
#include "election.h"
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>
#include <QMessageBox>
#include <QToolButton>
#include <QToolBar>
#include <QApplication>
using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QStackedLayout *ml;
    void make_tab1();
    void make_tab2();
    QTableWidget *tab,*states;
    void load_content();
    void get_states();
    QString file_saving_mode();
    QStringList get_precents_by_country(QString cnty,QString state);
    size_t get_total_country_votes(QString cnty,QString state);
    QStringList get_countries_by_state(QString n);
    QVector <election> results;
    void make_menu();
    QLabel *set;
    QChart *chart;
    QPieSeries *series;
    QChartView *view;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
  public slots:
    void showcountrieslist();
    void stateinfo();
    void showgraph();
    void mslot(QAction *);
};
#endif // MAINWINDOW_H
