#include "lesson.h"

Lesson::Lesson()
{
    lid=0;
    name="";
    semester=0;
}


Lesson::Lesson(int id,QString n,int s)
{
    lid=id;
    name=n;
    semester=s;
}


QString Lesson::getName() const
{
    return name;
}

int     Lesson::getLessonId() const
{
    return lid;
}

int     Lesson::getSemester() const
{
    return semester;
}

QString Lesson::toString()
{
    return QString::number(lid)+","+name+
            QString::number(semester);
}
