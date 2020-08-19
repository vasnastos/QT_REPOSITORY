#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include "structin.cpp"

class database
{
private:
    QSqlDatabase db;
    QByteArray to_bytearray(QPixmap &pix);
    QPixmap pixmap(QByteArray &arr);
public:
    database();
    ~database();
    void insert(QString name,QString id,QPixmap icon,double pr);
    QVector <product> products();
};

#endif // DATABASE_H
