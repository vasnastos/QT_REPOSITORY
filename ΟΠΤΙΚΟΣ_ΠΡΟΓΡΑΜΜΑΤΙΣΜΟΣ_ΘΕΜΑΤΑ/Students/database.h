#ifndef DATABASE_H
#define DATABASE_H
# include <QSqlDatabase>
# include <QSqlQuery>
# include <QString>
# include <QVariant>
# include <student.h>
# include <enroll.h>
# include <lesson.h>
# include <QVector>

class Database
{
private:
    QSqlDatabase db;
public:
    Database();
    void addStudent(Student &s);
    void addLesson(Lesson &l);
    void addEnroll(Enroll &e);
    bool existsStudent(Student &s);
    bool existsLesson(Lesson &l);
    bool existsEnroll(Enroll &e);
    QVector<Student> getStudents();
    QVector<Lesson>  getLessons();
    QVector<Enroll>  getEnrolls();
    QString getstudentlastname(int id);
    QString getlessonname(int lid);
    void    deleteStudent(Student &s);
    void    deleteLesson(Lesson &l);
    void    deleteEnroll(Enroll &e);
};

#endif // DATABASE_H
