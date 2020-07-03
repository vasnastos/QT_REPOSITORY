#include "student.h"

student::student(int i,QString name,int s):id(i),n(name),sem(s) {}
student::~student() {}
int student::getid()const {return this->id;}
QString student::getn()const {return this->n;}
int student::getsem()const {return this->sem;}
QString student::to_str() {return QString::number(this->id)+","+this->n+","+QString::number(this->sem);}
