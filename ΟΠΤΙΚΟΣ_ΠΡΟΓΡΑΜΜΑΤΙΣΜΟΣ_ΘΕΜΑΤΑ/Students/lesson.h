#ifndef LESSON_H
#define LESSON_H
# include <QString>

class Lesson
{
private:
    int lid;
    QString name;
    int semester;
public:
    Lesson();
    Lesson(int id,QString n,int s);
    QString getName() const;
    int     getLessonId() const;
    int     getSemester() const;
    QString toString();
};

#endif // LESSON_H
