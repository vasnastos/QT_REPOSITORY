#ifndef LESSON_H
#define LESSON_H
#include <QString>

class lesson
{
private:
    int id;
    QString name;
    double grade;
public:
    lesson(int i,QString ln,double g);
    int getid()const;
    QString getname()const;
    double getgrade()const;
};

#endif // LESSON_H
