#include "lesson.h"

lesson::lesson(int i,QString ln,double g):id(i),name(ln),grade(g) {}
int lesson::getid()const {return this->id;}
QString lesson::getname()const {return this->name;}
double lesson::getgrade()const {return this->grade;}
