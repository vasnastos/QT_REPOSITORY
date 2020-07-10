#ifndef RECORD_H
#define RECORD_H
#include <QString>

class record
{
private:
    int period;
    QString type;
    QString region;
    int count;
public:
    record(int p,QString t,QString r,int c);
    void setCount(int cnt);
    int get_period()const;
    QString get_type()const;
    QString get_region()const;
    int get_count()const;
    QString to_str();
};

#endif // RECORD_H
