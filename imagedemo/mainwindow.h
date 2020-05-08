#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "database.h"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QIntValidator>
#include <QLineEdit>
#include <QFileDialog>
#include <QDoubleSpinBox>
#include <QDesktopWidget>
#include <QMessageBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QTabWidget *tab;
    QLineEdit *id,*cat;
    QDoubleSpinBox *price,*ch1,*ch2;
    QLabel *label;
    database *mydb;
    QPixmap pix;
    QTableWidget *table,*tw;
    void tab1();
    void tab2();
    void tab3();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadimage();
    void addslot();
    void clearslot();
    void show_product();
    void catalog();
};
#endif // MAINWINDOW_H
