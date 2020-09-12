#include "database.h"

database::database()
{
  db=QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("company.db");
  db.open();
  QSqlQuery q(db);
  QString sql="create table if not exists Department(depid integer,depname varchar(50),primary key(depid))";
  q.exec(sql);
  sql="create table if not exists Employee(empid integer,empname varchar(60),depid integer,salary double,primary key(empid,depid))";
  q.exec(sql);
}
database::~database() {db.close();}

void database::insert_employee(int empid, QString name, int depid, double salary)
{
    QString sql="insert into Employee(empid,empname,depid,salary) values(?,?,?,?)";
    QSqlQuery q(db);
    q.prepare(sql);
    q.addBindValue(empid);
    q.addBindValue(name);
    q.addBindValue(depid);
    q.addBindValue(salary);
    q.exec();
}

void database::insert_department(int id, QString name)
{
    QString sql="insert into Department(depid,depname) values(?,?)";
    QSqlQuery q(db);
    q.prepare(sql);
    q.addBindValue(id);
    q.addBindValue(name);
    q.exec();
}

QVector <employee> database::get_dep_workers(int depid)
{
    QVector <employee> emps;
    QString sql="select empid,empname,salary from Employee where depid="+QString::number(depid);
    QSqlQuery q(db);
    q.exec(sql);
    while(q.next())
    {
        employee e(q.value(0).toString(),q.value(1).toInt(),q.value(2).toDouble());
        emps<<e;
    }
    return emps;
}

double database::get_dep_avg_salary(QString depname)
{
    QString sql="select depid from Department where depname='"+depname+"'";
    QSqlQuery q(db);
    q.next();
    int did=q.value(0).toInt();
    sql="select avg(salary) from Employee where depid="+QString::number(did);
    q.exec(sql);
    q.next();
    return q.value(0).toDouble();
}

QVector <department> database::departments()
{
    QVector <department> deps;
    QSqlQuery q(db);
    q.exec("select * from Department");
    while(q.next())
    {
        department d(q.value(0).toInt(),q.value(1).toString());
        deps<<d;
    }
    return deps;
}

bool database::employeein(int id)
{
    QSqlQuery q(db);
    q.exec("select * from Employee where empid="+QString::number(id));
    return q.next();
}

bool database::departmentin(int depid)
{
    QSqlQuery q(db);
    q.exec("select * from Department where depid="+QString::number(depid));
    return q.next();
}
