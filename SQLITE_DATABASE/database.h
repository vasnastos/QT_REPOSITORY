#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "employee.h"
#include "department.h"

class database
{
private:
    QSqlDatabase db;
public:
    database();
    ~database();
    void insert_department(int id,QString name);
    void insert_employee(int empid,QString name,int depid,double salary);
    QVector <employee> get_dep_workers(int depid);
    double get_dep_avg_salary(QString depname);
    QVector <department> departments();
    bool employeein(int id);
    bool departmentin(int depid);
};

#endif // DATABASE_H
