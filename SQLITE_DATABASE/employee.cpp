#include "employee.h"

employee::employee(QString n,int i,double s):name(n),id(i),salary(s) {}
int employee::get_id() {return this->id;}
double employee::get_salary() {return this->salary;}
QString employee::get_name() {return this->name;}
QString employee::to_str()
{
    return this->name+"--"+QString::number(this->id)+"--"+QString::number(this->salary);
}
