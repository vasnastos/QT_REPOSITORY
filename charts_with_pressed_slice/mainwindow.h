#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QChart>
#include <QPieSeries>
#include <QChartView>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMainWindow>
#include <QTableWidget>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>

using namespace QtCharts;

struct opsys
{
    QString Date;
    QVector <double> percents;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
  QWidget *mw;
  QVBoxLayout *lay;
  QChart *chart;
  QVector <opsys> recs;
  QPieSeries *series;
  QChartView *vw;
  QStringList fillcombo();
  QStringList os;
  QComboBox *dates;
  QTableWidget *tab;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void exportslot();
    void showdata();
    void pressedslice();
};
#endif // MAINWINDOW_H
