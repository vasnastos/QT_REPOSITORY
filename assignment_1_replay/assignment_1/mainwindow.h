#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QTextStream>
#include <QTableWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QPixmap>
#include "sources.cpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVector <line> lines;
    QVBoxLayout *ml;
    QTableWidget *tab;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void sumslot();
    void sqrtslot();
    void averageslot();
    void maxslot();
    void showslot();
    void loadslot();
    void saveslot();
    void clearslot();
};
#endif // MAINWINDOW_H
