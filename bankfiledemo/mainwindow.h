#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTabWidget>
#include <QApplication>
#include <QTableWidget>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QPushButton>
#include "dialog.h"

class account
{
private:
    QString accnum;
    QVector <double> balances;
public:
    account(QString acc):accnum(acc) {}
    void add_account(const double &d) {balances.append(d);}
    QString getaccnumber()const {return this->accnum;}
    QString to_str()
    {
        QString k="ACCOUNT_NUMBER:"+accnum;
        k+="\n BALANCES::\n";
        for(auto &x:balances)
        {
            k+="BALANCE::"+QString::number(x)+"\n";
        }
        return k;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QTabWidget *tab;
    QVector <QString> accountnumbers;
    QVector <account> accounts;
    QLabel *showlabel;
    QTableWidget *table;
    void tab1();
    void tab2();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void saveslot();
    void searchslot();
    void quitslot();
};
#endif // MAINWINDOW_H
