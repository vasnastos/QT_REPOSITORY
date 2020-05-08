#include "database.h"
QByteArray database::convert_pixmap(QPixmap pix)
{
    QByteArray array;
    QBuffer buffer(&array);
    buffer.open(QIODevice::WriteOnly);
    pix.save(&buffer,"PNG");
    return array;
}
QPixmap database::convert_bytearray(QByteArray arr)
{
    QPixmap pix;
    pix.loadFromData(arr);
    return pix;
}
database::database()
{
  db=QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("DEMO.db");
  db.open();
  QString sql="create table if not exists product(id integer,category text,photo blob,price double,primary key(id))";
  QSqlQuery q(db);
  if(q.exec(sql))
  {
      qDebug()<<"Hello new board from database"<<endl;
  }
}
void database::insert_product(product &p)
{
    QSqlQuery q(db);
    QString sql="insert into product(id,category,photo,price) values(?,?,?,?)";
    QByteArray byte=convert_pixmap(p.getimage());
    q.prepare(sql);
    q.addBindValue(p.getid());
    q.addBindValue(p.getcategory());
    q.addBindValue(byte);
    q.addBindValue(p.getprice());
    if(q.exec())
    {
        qDebug()<<"query execute"<<endl;
    }
}
QVector<product> database::getproducts()
{
    QVector <product> products;
    QSqlQuery q(db);
    q.exec("select * from product group by category");
    while(q.next())
    {
        QPixmap pix=convert_bytearray(q.value(2).toByteArray());
        product p(q.value(0).toInt(),pix,q.value(1).toString(),q.value(3).toDouble());
        products<<p;
    }
    return products;
}
double database::find_Average_price()
{
    QSqlQuery q(db);
    q.exec("select avg(price) from product");
    q.next();
    return q.value(0).toDouble();
}
bool database::is_in(int id)
{
    QSqlQuery qr(db);
    qr.exec("select id from product where id="+QString::number(id));
    return qr.first();
}
double database::max()
{
    double mx=3.0;
    QSqlQuery q(db);
    q.exec("select max(price) from product");
    q.next();
    mx=q.value(0).toDouble();
    return mx;
}
double database::min()
{
    double mn=3.0;
    QSqlQuery q(db);
    q.exec("select min(price) from product");
    q.next();
    mn=q.value(0).toDouble();
    return mn;
}
QVector<product> database::getbyprice(double mx1,double mx2)
{
    QVector <product> products;
    if(mx1>mx2)
    {
        double temp=mx1;
        mx1=mx2;
        mx2=temp;
    }
    QSqlQuery q(db);
    q.exec("select * from product where price between mx1 and mx2");
    while(q.next())
    {
        QPixmap pix=convert_bytearray(q.value(2).toByteArray());
        product p(q.value(0).toInt(),pix,q.value(1).toString(),q.value(3).toDouble());
        products<<p;
    }
    return products;
}
QStringList database::getcategories()
{
    QStringList list;
    QSqlQuery q(db);
    q.exec("select distinct category from product");
    while(q.next())
    {
       list<<q.value(0).toString();
    }
    return list;
}
QVector<product> database::sort_by_price()
{
    QVector<product> products;
    QSqlQuery q(db);
    q.exec("select * from product order by price");
    while(q.next())
    {
        QPixmap pix=convert_bytearray(q.value(2).toByteArray());
        product p(q.value(0).toInt(),pix,q.value(1).toString(),q.value(3).toDouble());
        products<<p;
    }
    return products;
}
