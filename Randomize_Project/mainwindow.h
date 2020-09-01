#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMovie>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <random>
#include <QDebug>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QPushButton *b,*b1;
    std::mt19937 mt();
    std::uniform_int_distribution <int> num();
    QChart *chart;
    QVector <int> numbers;
    QPieSeries *series;
    QChartView *view;
signals:
    void valueadded();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void add_random();
    void sum();
    void average();
    void reinform();
};
#endif // MAINWINDOW_H
