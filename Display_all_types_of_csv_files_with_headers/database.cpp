#include "database.h"

database::database()
{
   db=QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("files.db");
   db.open();
   QSqlQuery q(db);
   q.exec("create table if not exists file(title varchar(40),contain text,primary key(title))");
}

database::~database() {db.close();}

void database::insert_file(QString title, QString text)
{
    QString sql="insert into file(title,contain) values(?,?)";
    QSqlQuery q(db);
    q.prepare(sql);
    q.addBindValue(title);
    q.addBindValue(text);
    q.exec();
}

bool database::is_in(QString tit)
{
    QSqlQuery q(db);
    q.exec("select * from file where title='"+tit+"'");
    return q.next();
}

QString database::get_file_by_title(QString tit)
{
    QString sql="select contain from file where title='"+tit+"'";
    QSqlQuery q(db);
    q.exec(sql);
    q.next();
    return q.value(0).toString();
}

QStringList database::get_saved_files()
{
    QStringList list;
    QSqlQuery q(db);
    q.exec("select title from file");
    while(q.next())
    {
        list<<q.value(0).toString();
    }
    return list;
}

void database::delete_record(QString t)
{
    QSqlQuery q(db);
    q.exec("delete from file where title='"+t+"'");
}
