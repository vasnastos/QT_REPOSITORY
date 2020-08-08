#include "database.h"
#include <QDebug>

database::database(QString name)
{
  db=QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(name);
  db.open();
  QSqlQuery q(db);
  QString sql="create table if not exists book(name varchar(40),code integer,address text,phone varchar(10))";
  if(q.exec(sql))
      qDebug()<<"Hello world";
}

database::~database() {db.close();}

void database::insert(QString n, QString ad, QString ph, int cd)
{
    QString sql="insert into book(name,code,address,phone) values(?,?,?,?)";
    QSqlQuery query(db);
    query.prepare(sql);
    query.addBindValue(n);
    query.addBindValue(cd);
    query.addBindValue(ad);
    query.addBindValue(ph);
    if(query.exec())
        qDebug()<<"Insertion complete"<<endl;
}

QVector <record>  database::get_records()
{
    QVector <record> recs;
    QString sql="select * from book";
    QSqlQuery q(db);
    q.exec(sql);
    while(q.next())
    {
        record r;
        r.name=q.value(0).toString();
        r.code=q.value(1).toInt();
        r.address=q.value(2).toString();
        r.phone=q.value(3).toString();
        recs<<r;
    }
    return recs;
}

bool database::record_exist(QString name, QString ad, QString ph)
{
    QSqlQuery q(db);
    q.exec("select * from book where name='"+name+"' and address='"+ad+"' and phone='"+ph+"'");
    if(q.next())
    {
        QMessageBox::critical(nullptr,"ERROR","This record already exists in database");
        return true;
    }
    return q.next();
}

QStringList database::codes()
{
    QStringList codes;
    QSqlQuery q(db);
    q.exec("select distinct code from book");
    while(q.next())
    {
        codes<<q.value(0).toString();
    }
    return codes;
}

void database::search(QString name)
{
    QSqlQuery q(db);
    q.exec("select code,phone,address from book where name='"+name+"'");
    QString msg="<p style=text-align:center; color:red;>INFO</p>";
    msg+="<ul>";
    if(!q.next())
    {
        QMessageBox::critical(nullptr,"Info","No such name found");
        return;
    }
    else
    {
        msg+="<li>";
        msg+=q.value(0).toString()+","+q.value(1).toString()+","+q.value(2).toString();
        msg+="</li>";
    }
    while(q.next())
    {
        msg+="<li>";
        msg+=q.value(0).toString()+","+q.value(1).toString()+","+q.value(2).toString();
        msg+="</li>";
    }
    msg+="</ul>";
    QMessageBox::information(nullptr,"NAME:"+name,msg);
}
