#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "students.cpp"
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QMenu>
#include <QMenuBar>
#include <QFile>
#include <QSlider>
#include <QFileDialog>
#include <QTextStream>
#include <QLineEdit>
#include <QVector>
#include <QDesktopWidget>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
class mainwindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QMenuBar *bar;
    QMenu *fm;
    QLineEdit *id,*n;
    QPushButton *b,*b1;
    QVector <QSlider *> sl;
    QVector <QLabel *> lb;
    QVector <student> students;
    QTableWidget *tab;
public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
signals:
    void tabshow();
public slots:
    void menuslot(QAction *ac);
    void addslot();
    void sortslot();
    void tablechanges();
    void priceslot(int v);
};
#endif // MAINWINDOW_H
