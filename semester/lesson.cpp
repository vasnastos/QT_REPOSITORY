#include "lesson.h"

lesson::lesson(QString n,int s):ln(n),sm(s) {}
QString lesson::getln()const {return this->ln;}
int lesson::getsm()const {return this->sm;}
QString lesson::tostr() {return this->ln+","+QString::number(this->sm);}
