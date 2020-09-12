#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>

class employee
{
private:
   QString name;
   int id;
   double salary;
public:
    employee(QString n,int i,double s);
    int get_id();
    double get_salary();
    QString get_name();
    QString to_str();
};

#endif // EMPLOYEE_H
