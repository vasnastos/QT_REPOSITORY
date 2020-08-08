#ifndef SHOWDIALOG_H
#define SHOWDIALOG_H
#include <QDialog>
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QObject>
#include <QTableWidget>
#include "database.h"

class showdialog:public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *lay;
    database *db;
    QComboBox *bx;
    QTableWidget *tb;
public:
    showdialog(database &d,QWidget *p=nullptr);
public slots:
    void comboslot(QString text);
};

#endif // SHOWDIALOG_H
