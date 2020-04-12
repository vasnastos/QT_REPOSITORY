#include <QString>
#include <QVector>
struct student
{
    int id;
    QString name;
    QVector <int> grades;
    double avg;
    bool operator>(student s) {return avg>s.avg;}
    student &operator=(student s)
    {
        id=s.id;
        name=s.name;
        grades.clear();
        for(int i=0;i<s.grades.size();i++)
        {
            grades<<s.grades[i];
        }
        avg=s.avg;
        return *this;
    }
    QString tostring()
    {
        QString in=QString::number(id)+","+name+",";
        for(int i=0;i<grades.size();i++)
        {
            in+=QString::number(grades[i])+",";
        }
        in+=QString::number(avg);
        return in;
    }
};
