#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

class database
{
    QSqlDatabase db;
public:
    database();
    ~database();
    bool is_in(QString tit);
    void insert_file(QString title,QString text);
    QString get_file_by_title(QString tit);
    QStringList get_saved_files();
    void delete_record(QString t);
};

#endif // DATABASE_H
