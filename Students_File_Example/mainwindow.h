#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFileDialog>
#include <QFile>
#include <QApplication>
#include <QDoubleSpinBox>
#include <QTextStream>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QVector>
#include "information.cpp"
#include <QMenu>
#include <QComboBox>
#include <QTableWidget>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    //Πρόγραμμα καταγραφής απόδοσης φοιτητών σε 3 εξαμηνιαία μαθήματα.
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *layout;
    QTableWidget *table;
    QComboBox *lesson;
    QVector <student> students;
    QVector <QDoubleSpinBox *> grbox;
    void make_menu();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void show_pass_slot();
    void menuslot(QAction *a);
    void lessondetails(QString x);
    void updateslot();
};
#endif // MAINWINDOW_H
