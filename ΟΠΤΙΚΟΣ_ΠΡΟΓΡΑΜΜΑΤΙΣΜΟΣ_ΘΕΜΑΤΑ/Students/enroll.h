#ifndef ENROLL_H
#define ENROLL_H
# include <QString>

class Enroll
{
private:
    int sid,lid;
public:
    Enroll();
    Enroll(int s,int l);
    int getStudentId() const;
    int getLessonId() const;
    QString toString();
};

#endif // ENROLL_H
