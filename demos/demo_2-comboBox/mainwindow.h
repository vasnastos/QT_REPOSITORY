#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QApplication>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QMenu>
#include <QMenuBar>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

struct population
{
    QString period;
    QString status;
    QString gender;
    QString age;
    size_t count;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QComboBox *box;
    QVector <population> pops;
    void make_menu();
    QChart *ch;
    QPieSeries *series;
    QChartView *view;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void comboage(QString ag);
    void showgraph();
    void menuslot(QAction *a);
    void editslot(QAction *ac);
};
#endif // MAINWINDOW_H
