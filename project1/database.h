#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include <QString>
#include "lesson.h"
#include "details.cpp"
class database
{
private:
    QSqlDatabase db;
public:
    database();
    ~database();
    void insert(lesson &l);
    QVector <detail> getlessondetails(QString ln);
    QVector<QString> getlessonnames();
    void deletestudent(int id);
    QVector<precent> getprecent();//pass precent for all lessons enroll
};

#endif // DATABASE_H
