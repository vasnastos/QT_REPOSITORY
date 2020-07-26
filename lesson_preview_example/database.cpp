#include "database.h"

database::database()
{
  db=QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("details.db");
  db.open();
  QSqlQuery q(db);
  QString sql="create table if not exists Lesson(title varchar(30),id integer,grade double,primary key(title,id))";
  q.exec(sql);
}

database::~database() {db.close();}

void database::insert_lesson(QString name, int id, double fg)
{
    QSqlQuery q(db);
    q.prepare("insert into Lesson(title,id,grade) values(?,?,?)");
    q.addBindValue(name);
    q.addBindValue(id);
    q.addBindValue(fg);
    q.exec();
}

QVector <dets> database::get_lesson_dets(QString ln)
{
    QVector <dets> details;
    QSqlQuery q(db);
    QString sql="select id,grade from Lesson where title='"+ln+"'";
    q.exec(sql);
    while(q.next())
    {
        dets l;
        l.id=q.value(0).toInt();
        l.fg=q.value(1).toDouble();
        details<<l;
    }
    return details;
}

QStringList database::getlessons()
{
    QStringList lessons;
    QSqlQuery q(db);
    q.exec("select distinct title from Lesson");
    while(q.next())
    {
        lessons.append(q.value(0).toString());
    }
    return lessons;
}
