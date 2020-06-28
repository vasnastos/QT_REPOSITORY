#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QTextStream>
#include <QPushButton>
#include <QMessageBox>
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
    QTextEdit *ed;
    QChart *chart;
    QPieSeries *series;
    QChartView *view;
    QVector <int> res;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void showslot();
    void clearslot();
};
#endif // MAINWINDOW_H
