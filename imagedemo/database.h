#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QBuffer>
#include <QDebug>
#include "product.h"
class database
{
private:
    QSqlDatabase db;
    QByteArray convert_pixmap(QPixmap pix);
    QPixmap convert_bytearray(QByteArray arr);
public:
    database();
    void insert_product(product &p);
    QVector <product> getproducts();
    double find_Average_price();
    double max();
    double min();
    QVector<product> getbyprice(double mx1,double mx2);
    bool is_in(int id);
    QStringList getcategories();
    QVector<product> sort_by_price();
};

#endif // DATABASE_H
