#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QApplication>
#include <QDebug>
#include "database.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QTableWidget *tab;
    database *mydb;
    QLineEdit *title;
    QComboBox *titles;
    QStringList spl;
    void make_menu();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void menuslot(QAction *a);
    void uploadslot();
    void saveslot();
    void deleteslot();
};
#endif // MAINWINDOW_H
