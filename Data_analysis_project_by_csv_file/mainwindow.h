#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>
#include <QPushButton>
#include <QMenuBar>
#include <QFileDialog>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <QVBoxLayout>
#include <QApplication>
#include <QComboBox>
#include <QTableWidget>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

struct abortion
{
    int year;
    QString age;
    double rate;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    void make_menu();
    QTableWidget *tab;
    QComboBox *combo;
    QChart *chart;
    QPieSeries *series;
    QPieSlice *slice;
    QChartView *view;
    QVector <abortion> abortinfo;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void added();
public slots:
    void menuslot(QAction *a);
    void rateperyearslot();
    void avgrateslot();
    void Statsperyear();
    void tableview();
};
#endif // MAINWINDOW_H
