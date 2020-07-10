#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QTextStream>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include "record.h"
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
    QVector <record> records;
    QLineEdit *p,*tp,*r,*c;
    QTableWidget *tab;
    QChart *chart;
    QPieSeries *srs;
    QChartView *vw;
    QString db_sim;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void recordadd();
public slots:
    void addslot();
    void saveslot();
    void addemit();
};
#endif // MAINWINDOW_H
