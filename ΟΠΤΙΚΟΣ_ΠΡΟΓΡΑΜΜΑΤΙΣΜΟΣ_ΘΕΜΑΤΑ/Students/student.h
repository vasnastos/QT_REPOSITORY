#ifndef STUDENT_H
#define STUDENT_H
# include <QString>
# include <QVector>
class Student
{
private:
    int sid;
    QString name;
    QString lastname;
public:
    Student();
    Student(int s,QString n,QString l);
    double getLesson(int pos) const;
    int getId() const;
    QString getName() const;
    QString getLastname() const;
    QString toString();
};

#endif // STUDENT_H
