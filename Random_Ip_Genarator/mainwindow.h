#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QList>
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QChart>
#include <QLineEdit>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QPieSeries>
#include <QChartView>
#include <QApplication>
#include <QScrollBar>
#include <QTextEdit>

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QLineEdit *num;
    QTextEdit *showlb;
     QChart *chart;
     QStringList ips;
     void make_menu();
     QPieSeries *series;
     QChartView *view;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void genarate();
    void menuslot(QAction *a);
    void showipslot();
};
#endif // MAINWINDOW_H
