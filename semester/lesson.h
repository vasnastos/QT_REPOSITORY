#ifndef LESSON_H
#define LESSON_H
#include <QString>

class lesson
{
private:
    QString ln;
    int sm;
public:
    lesson(QString n,int s);
    QString getln()const;
    int getsm()const;
    QString tostr();
};

#endif // LESSON_H
