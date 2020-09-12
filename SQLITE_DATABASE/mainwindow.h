#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QTableWidget>
#include <QLineEdit>
#include "database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QLineEdit *n,*id,*did,*sl,*depid,*dname;
    QTableWidget *tab;
    database *mydb;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void renew();
public slots:
    void addslot();
    void depment();
    void newtab();
    void employees();
};
#endif // MAINWINDOW_H
