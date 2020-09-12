#include "department.h"

department::department(int id,QString n):depid(id),name(n) {}
int department::get_id() {return this->depid;}
QString department::getname() {return this->name;}
