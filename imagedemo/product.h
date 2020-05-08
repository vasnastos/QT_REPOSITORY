#ifndef PRODUCT_H
#define PRODUCT_H
#include <QPixmap>
#include <QString>

class product
{
private:
    int id;
    QPixmap image;
    QString category;
    double price;
public:
    product(int i,QPixmap pix,QString d,double pr);
    void set_pixmap(QPixmap p);
    int getid()const;
    QPixmap getimage();
    QString getcategory()const;
    double getprice()const;
};

#endif // PRODUCT_H
