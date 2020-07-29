#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFile>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QTextStream>
#include <QApplication>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QLineEdit *to;
    QDoubleSpinBox *f;
    QComboBox *bx,*tbx;
    void make_menu();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void act(QString x);
    void menuslot(QAction *a);
    void colorslot(QAction *ac);
};
#endif // MAINWINDOW_H
