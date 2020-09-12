#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <QString>

class department
{
private:
    int depid;
    QString name;
public:
    department(int id,QString n);
    int get_id();
    QString getname();
};

#endif // DEPARTMENT_H
