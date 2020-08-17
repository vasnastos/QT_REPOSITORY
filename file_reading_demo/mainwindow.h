#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QMovie>
#include <QKeyEvent>
#include <QFileDialog>
#include <QTextStream>
#include <QComboBox>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

struct popul
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
    QChart *chart;
    QPieSeries *series;
    QChartView *view;
    QStringList get_ages();
    QVector <popul> pop;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *ev);
public slots:
    void loadslot();
    void comboslot(QString key);
};
#endif // MAINWINDOW_H
