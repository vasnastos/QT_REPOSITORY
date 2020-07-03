#include "enroll.h"

Enroll::Enroll()
{
    sid=0;
    lid=0;
}


Enroll::Enroll(int s,int l)
{
    sid=s;
    lid=l;
}

int Enroll::getStudentId() const
{
    return sid;
}

int Enroll::getLessonId() const
{
    return lid;
}

QString Enroll::toString()
{
    return QString::number(sid)+","+QString::number(lid);
}
