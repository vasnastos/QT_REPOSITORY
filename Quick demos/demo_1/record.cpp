#include "record.h"

record::record(int p,QString t,QString r,int c):period(p),type(t),region(r),count(c) {}
void record::setCount(int cnt) {this->count=cnt;}
int record::get_period()const {return this->period;}
QString record::get_type()const {return this->type;}
QString record::get_region()const {return this->region;}
int record::get_count()const {return this->count;}
QString record::to_str()
{
    return QString::number(this->period)+"--"+this->type+"--"+this->region+"--"+QString::number(this->count);
}
