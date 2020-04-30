#include "database.h"

database::database()
{
   if(db.isOpen()) db.close();
   db=QSqlDatabase::addDatabase("QSQLITE");
   db.setDatabaseName("Demo.db");
   db.open();
   QSqlQuery q(db);
   if(q.exec(QString("create table if not exists lesson(")+
          QString("name varchar(20),")+
          QString("id integer,")+
          QString("grade double,")+
          QString("primary key(name,id))")))
       qDebug()<<"Hello world from database"<<endl;
}
database::~database() {db.close();}
void database::insert(lesson &l)
{
    QSqlQuery q(db);
    q.prepare("insert into lesson(name,id,grade) values(:name,:id,:grade)");
    q.bindValue(":name",l.getname());
    q.bindValue(":id",l.getid());
    q.bindValue(":grade",l.getgrade());
    q.exec();
}
QVector<detail> database::getlessondetails(QString ln)
{
   QVector<detail> vec;
   QSqlQuery q(db);
   q.exec("select id,grade from lesson where name='"+ln+"'");
   while(q.next())
   {
       detail det;
       det.id=q.value(0).toInt();
       det.gr=q.value(1).toDouble();
       vec<<det;
   }
   return vec;
}
QVector<QString> database::getlessonnames()
{
    QVector<QString> vec;
    QSqlQuery q(db);
    q.exec("select distinct name from lesson");
    while(q.next())
    {
        vec<<q.value(0).toString();
    }
    return vec;
}
void database::deletestudent(int id)
{
    QSqlQuery q(db);
    q.exec("delete from lesson where id="+QString::number(id));
}
QVector<precent> database::getprecent()
{
    QVector<int> numbers;
    QVector<precent> vec;
    QSqlQuery qr(db);
    qr.exec("select count(id) from lesson group by name");
    while(qr.next())
    {
        numbers<<qr.value(0).toInt();
    }
    qr.exec("select count(grade),lesson from lesson where grade>=5.0 group by name");
    int i=0;
    while(qr.next())
    {
        precent prc;
        prc.pr=(qr.value(0).toDouble()/numbers.at(i))*100.0;
        prc.name=qr.value(1).toString();
        vec<<prc;
        i++;
    }
    return vec;
}
