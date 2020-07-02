#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QFile>
#include <QTextStream>
#include <QPushButton>
#include <QFileDialog>
#include <QLabel>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

struct product
{
    QString desc;
    int quantiny;
    double price;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QVector <product> prods;
    QWidget *mw;
    QVBoxLayout *ml;
    QTableWidget *tab;
    QChart *chart;
    QPieSeries *series;
    QChartView *view;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void exportslot();
    void showprice();
    void showquantity();
    void showtab();
};
#endif // MAINWINDOW_H
