#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include "structin.cpp"
#include <QVariant>

class database
{
private:
    QSqlDatabase db;
public:
    database(QString name);
    ~database();
    void insert(QString n,QString ad,QString ph,int cd);
    QVector <record> get_records();
    bool record_exist(QString name,QString ad,QString ph);
    QStringList codes();
    void search(QString name);
};

#endif // DATABASE_H
