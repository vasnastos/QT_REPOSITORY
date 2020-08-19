#include "database.h"
#include <QBuffer>

QByteArray database::to_bytearray(QPixmap &pix)
{
    QByteArray b;
    QBuffer buf(&b);
    buf.open(QIODevice::WriteOnly);
    pix.save(&buf,"png");
    return b;
}

QPixmap database::pixmap(QByteArray &arr)
{
    QPixmap p;
    p.loadFromData(arr);
    return p;
}

database::database()
{
  db=QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("products.db");
  db.open();
  QString sql="create table if not exists product(name text,id text,image blob,price double,primary key(id))";
  QSqlQuery q(db);
  q.exec(sql);
}

database::~database() {db.close();}

void database::insert(QString name, QString id, QPixmap icon, double pr)
{
    QString preparequery="insert into product(name,id,image,price) values(?,?,?,?)";
    QSqlQuery query(db);
    query.prepare(preparequery);
    QByteArray array=to_bytearray(icon);
    query.addBindValue(name);
    query.addBindValue(id);
    query.addBindValue(array);
    query.addBindValue(pr);
    query.exec();
}

QVector <product> database::products()
{
    QVector <product> prods;
    QSqlQuery q(db);
    q.exec("select * from product");
    while(q.next())
    {
        product p;
        p.name=q.value(0).toString();
        p.id=q.value(1).toString();
        QByteArray b=q.value(2).toByteArray();
        p.pix=this->pixmap(b);
        p.price=q.value(3).toDouble();
        prods<<p;
    }
    return prods;
}
