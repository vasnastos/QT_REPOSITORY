#include "student.h"

Student::Student()
{

}
Student::Student(int s,QString n,QString l)
{
    sid=s;
    name=n;
    lastname=l;
}


int Student::getId() const
{
    return sid;
}

QString Student::getName() const
{
    return name;
}

QString Student::getLastname() const
{
    return lastname;
}

QString Student::toString()
{
    return QString::number(sid)+","+
            name+","+lastname;
}
