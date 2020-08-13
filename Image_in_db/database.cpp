#include "database.h"
#include <QBuffer>
#include <QPixmap>

QByteArray database::to_byte_form(QPixmap &pix)
{
   QByteArray array;
   QBuffer buffer(&array);
   buffer.open(QIODevice::WriteOnly);
   pix.save(&buffer,"png");
   return array;
}

QPixmap database::to_image(QByteArray array)
{
    QPixmap picture;
    picture.loadFromData(array);
    return picture;
}

database::database()
{
   db=QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("pictures.db");
   db.open();
   QSqlQuery q(db);
   q.exec("create table if not exists image(title varchar(40),picture blob,primary key(title))");
}

database::~database() {db.close();}

void database::insert(QString tit, QPixmap px)
{
    QString sql="insert into image(title,picture) values(?,?)";
    QSqlQuery query(db);
    query.prepare(sql);
    QByteArray barray=to_byte_form(px);
    query.addBindValue(tit);
    query.addBindValue(barray);
    query.exec();
    QMessageBox::information(nullptr,"Info","Insertion complete");
}

QVector <std::tuple<QString,QPixmap>> database::get_records()
{
    QVector <std::tuple<QString,QPixmap>> records;
    QSqlQuery q(db);
    q.exec("select * from image");
    while(q.next())
    {
        QPixmap pct=to_image(q.value(1).toByteArray());
        std::tuple <QString,QPixmap> rec=std::make_tuple(q.value(0).toString(),pct);
        records.append(rec);
    }
    return records;
}
