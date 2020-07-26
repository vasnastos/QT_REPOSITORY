#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include "database.h"
#include <QComboBox>
#include <QHBoxLayout>
#include <QPushButton>

class dialog:public QDialog
{
    Q_OBJECT
private:
    QComboBox *bx;
    QVBoxLayout *ml;
    QHBoxLayout *lay;
    database *dialdb;
    QString selectedlesson;
    QVector <dets> dts;
public:
    dialog(database &d,QWidget *p=nullptr);
    ~dialog();
    QVector <dets> getdetsvector();
    QString getselectedlesson();
public slots:
    void selectslot();
};

#endif // DIALOG_H
