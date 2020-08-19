#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTextStream>
#include "database.h"
#include <QPushButton>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QLineEdit *n,*code,*price;
    QLabel *prev;
    database *mdb;
    QPixmap pix;
    QTableWidget *tab;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void recordadded();
public slots:
    void renew();
    void loadslot();
    void uploadslot();
};
#endif // MAINWINDOW_H
