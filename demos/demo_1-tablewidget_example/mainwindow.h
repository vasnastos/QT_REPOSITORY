#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QVBoxLayout>
#include <QTextStream>
#include <QFileDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

struct divorce
{
    int year;
    QString gender;
    double avegage;
    double precent;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QTableWidget *tab;
    QChart *chart;
    QPieSeries *srs;
    QVector <divorce> devs;
    QChartView *vw;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void saveslot();
    void showstats();
    void showgraph();
    void exportimage();
};
#endif // MAINWINDOW_H
