#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QMenu>
#include <QTextEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include "dialog.h"
#include "database.h"
#include "student.h"
#include "lesson.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QStackedLayout *ml;
    QLineEdit *i,*ns,*sem,*ln,*lsem,*sid;
    QComboBox *av_les,*performance;
    void makemenu();
    void makelineedit();
    void makelineedit2();
    void maketab3();
    database *mydb;
    QComboBox *lesn,*enid;
    QTableWidget *tab,*ltab,*grades;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void stmenu(QAction *ac);
    void lsmenu(QAction *a);
    void teachersslot(QAction *ta);
    void updatetable();
    void submitslot();
};
#endif // MAINWINDOW_H
