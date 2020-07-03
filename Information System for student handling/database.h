#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QInputDialog>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QFile>
#include "idresults.cpp"
#include "student.h"
#include "lesson.h"
#include "result.cpp"
class database
{
private:
    QSqlDatabase db;
public:
    database(QString name);
    ~database();
    void insert_student(student &s);
    void insert_lesson(lesson &l);
    void insert_enroll(int id,QString ln);
    void update_grade(int i,QString ln,double gr);
    QVector<resultsperid> findstudent(int id);
    student* getinfo(int id);
    void insert_credentials();
    bool lesson_is_in(QString ln);
    bool is_in(int id);
    bool credentialsexist(QString un,QString pas);
    bool is_in_enroll_lesson(QString a);
    bool already_enroll(QString ln,int id);
    bool delete_student(int am);
    bool delete_lesson(QString name);
    QStringList getlesson();
    QStringList getenrolledid();
    QStringList getstudents();
    QStringList getenrolledlessons();
    QStringList getavailablelessons();
    QVector <results> lesson_performance(QString ln);
};

#endif // DATABASE_H
