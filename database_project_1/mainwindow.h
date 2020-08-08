#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTableWidget>
#include "showdialog.h"
#include <QLineEdit>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QTableWidget *tab;
    QLineEdit *n,*p,*ad,*cd;
    QLineEdit *name;
    database *mydb;
    void make_register_form();
    void make_search_form();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void add();
public slots:
    void addslot();
    void searchslot();
    void regslot();
    void codeslot();
};
#endif // MAINWINDOW_H
