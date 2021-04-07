#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QDrag>
#include <QVBoxLayout>
#include "draglabel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *lay;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
