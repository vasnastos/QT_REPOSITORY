#ifndef STUDENT_H
#define STUDENT_H
#include <QString>

class student
{
private:
    int id;
    QString n;
    int sem;
public:
    student(int i,QString name,int s);
    ~student();
    int getid()const;
    QString getn()const;
    int getsem()const;
    QString to_str();
};

#endif // STUDENT_H
