#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFileDialog>
#include "database.h"
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QStackedLayout>
#include <QLabel>
#include <QLineEdit>


class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QStackedLayout *mainlay;
    QLineEdit *title;
    void win1();
    void win2();
    QLabel *lbl;
    QLabel *previewlabel;
    QLabel *showlabel;
    database *mydb;
    void make_menu();
    QPixmap pixmap;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void uploadslot();
    void localimage();
    void previewslot();
    void pagechange(QAction *a);
};
#endif // MAINWINDOW_H
