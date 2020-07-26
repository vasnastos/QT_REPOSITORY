#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "structuse.cpp"

class database
{
   private:
    QSqlDatabase db;
public:
    database();
    ~database();
    void insert_lesson(QString name,int id,double fg);
    QVector <dets> get_lesson_dets(QString ln);
    QStringList getlessons();
};

#endif // DATABASE_H
