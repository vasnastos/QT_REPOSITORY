#include "database.h"

database::database(QString name)
{
  if(db.isOpen()) db.close();
  db=QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(name);
  db.open();
  QSqlQuery q(db);
  q.prepare(QString("create table if not exists Student(")
           +QString("id Integer primary key,")
           +QString("name varchar(20),")
           +QString("semester integer)"));
           if(q.exec())
           {
               qDebug()<<"table Student has been created!!"<<endl;
           }
  q.prepare(QString("create table if not exists Lesson(")+
         QString("name varchar(20),")+
         QString("semester Integer,")
            +QString("primary key(name))"));
          if(q.exec())
          {
              qDebug()<<"table lesson has been created!!"<<endl;
          }
  q.prepare(QString("create table if not exists Enroll(")+
            QString("id Integer,")+
            QString("lessonname varchar(20),")+
            QString("grade double,")+
            QString("primary key(id,lessonname),")+
            QString("foreign key(id) references Student(id),")+
            QString("foreign key(lessonname) references Lesson(name))"));
   if(q.exec())
   {
       qDebug()<<"hello word from database!!!!";
   }
   if(q.exec(QString("create table if not exists credentials(")
          +QString("username text,password varchar(8))")))
       qDebug()<<"credentials enable";
}
database::~database() {db.close();}
void database::insert_student(student &s)
{
  QSqlQuery q(db);
  q.prepare("insert into Student(id,name,semester) values(:id,:name,:semester)");
  q.bindValue(":id",s.getid());
  q.bindValue(":name",s.getn());
  q.bindValue(":semester",s.getsem());
  if(q.exec())
  qDebug()<<"insertion of student complete";
}
void database::insert_lesson(lesson &l)
{
    QSqlQuery q(db);
    q.prepare("insert into Lesson(name,semester) values(?,?)");
    q.addBindValue(l.getln());
    q.addBindValue(l.getsm());
    if(q.exec())
    qDebug()<<"insertion of lesson complete";
    else
        qDebug()<<"error";
}
void database::insert_credentials()
{
    QSqlQuery q(db);
    QFile fp(":/credentials.txt");
    bool ok=fp.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ok) return;
    QTextStream st(&fp);
    while(!st.atEnd())
    {
        QString line=st.readLine();
        QStringList list=line.split("-");
        if(credentialsexist(list[0],list[1])) continue;
        q.prepare("insert into credentials(username,password) values(?,?)");
        q.addBindValue(list[0]);
        q.addBindValue(list[1]);
        q.exec();
    }
    fp.close();
}
bool database::credentialsexist(QString un,QString pas)
{
    QSqlQuery q(db);
    q.exec("select * from credentials where username='"+un+"' and password='"+pas+"'");
    return q.first();
}
void database::insert_enroll(int id, QString ln)
{
    if(!is_in(id))
    {
        qDebug()<<"Student doesn't exist in database"<<endl;
        return;
    }
    if(!lesson_is_in(ln))
    {
        qDebug()<<"lesson doesn't exist in database"<<endl;
        return;
    }
    QSqlQuery q(db);
    q.prepare("insert into Enroll(id,lessonname) values(?,?)");
    q.addBindValue(id);
    q.addBindValue(ln);
    if(q.exec())
        qDebug()<<"Enroll complete";
}
void database::update_grade(int i,QString ln,double gr)
{
  QSqlQuery q(db);
  q.exec("update Enroll set grade="+QString::number(gr)+" where id="+QString::number(i)+" and lessonname='"+ln+"'");
}
bool  database::delete_student(int am)
{
    QSqlQuery query(db);
    query.exec("delete from Student where id="+QString::number(am));
    query.exec("delete from Enroll where id="+QString::number(am));
    int count=0;
    query.exec("select count(*) from Student where id="+QString::number(am));
    query.next();
    count=query.value(0).toInt();
    query.exec("select count(*) from Enroll where id="+QString::number(am));
    query.next();
    count+=query.value(0).toInt();
    if(count==0) return true;
    return false;
}
bool database::delete_lesson(QString name)
 {
     bool check=false,check1=false;
     QSqlQuery q(db);
     q.exec("delete from Lesson where name='"+name+"'");
     q.exec("delete from Enroll where lessonname='"+name+"'");
     q.exec("select name from Lesson where name='"+name+"'");
     check=q.first();
     q.exec("select lessonname from Enroll where name='"+name+"'");
     check1=q.first();
     return (check && (check && check1));
 }
QVector<resultsperid> database::findstudent(int id)
{
    QVector<resultsperid> vec;
    QSqlQuery query(db);
    query.exec("Select lessonname,grade from Enroll where id="+QString::number(id));
    while(query.next())
    {
        resultsperid res;
        res.ln=query.value(0).toString();
        res.grade=query.value(1).toDouble();
        vec<<res;
    }
    return vec;
}
bool database::is_in(int id)
{
    QSqlQuery query(db);
    query.exec("Select id from Student where id="+QString::number(id));
    return query.first();
}
bool database::lesson_is_in(QString ln)
{
    QSqlQuery q(db);
    q.exec("select name from Lesson where name='"+ln+"'");
    return q.first();
}
bool database::already_enroll(QString ln,int id)
{
    QSqlQuery q(db);
    q.exec("select * from Enroll where lessonname='"+ln+"' and id="+QString::number(id));
    return q.first();
}
QStringList database::getenrolledid()
{
    QStringList list;
    QSqlQuery q(db);
    q.exec("select id,name from Student");
    while(q.next())
    {
        QString information=QString::number(q.value(0).toInt())+"-"+q.value(1).toString();
        list<<information;
    }
    return list;
}
QStringList database::getavailablelessons()
{
   QStringList list;
   list.clear();
   QSqlQuery q(db);
   q.exec("select name from Lesson");
   while(q.next())
   {
       list<<q.value(0).toString();
   }
   return list;
}
QVector <results> database::lesson_performance(QString ln)
{
  QVector <results> vec;
  QSqlQuery q(db);
  q.exec("select id,grade from Enroll where lessonname='"+ln+"'");
  while(q.next())
  {
      results tem;
      tem.am=q.value(0).toInt();
      tem.grade=q.value(1).toDouble();
      vec<<tem;
  }
  return vec;
}
bool database::is_in_enroll_lesson(QString a)
{
    QSqlQuery q(db);
    q.exec("select lessonname from Enroll where lessonname='"+a+"'");
    return q.first();
}

QStringList database::getstudents()
{
    QStringList info;
    QSqlQuery q(db);
    q.exec("select id,name from Student");
    while(q.next())
    {
        info<<QString::number(q.value(0).toInt())+"-"+q.value(1).toString();
    }
    return info;
}
QStringList database::getenrolledlessons()
{
    QStringList list;
    QSqlQuery q(db);
    q.exec("select distinct lessonname from Enroll");
    while(q.next())
    {
        list<<q.value(0).toString();
    }
    return list;
}
