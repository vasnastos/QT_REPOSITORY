#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QTextStream>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace  QtCharts;

struct student
{
    QString am;
    double theory;
    double lab;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QPushButton *b,*s;
    QStackedWidget *shwd;
    QTableWidget *pass;
    double thp,lbp;
    QTableWidget *fail;
    QChart *chr;
    QPieSeries *srs;
    QChartView *view;
    QVector <student> students;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void changewidget();
};
#endif // MAINWINDOW_H
