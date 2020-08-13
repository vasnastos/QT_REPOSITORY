#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>

class database
{
 private:
    QSqlDatabase db;
    QByteArray to_byte_form(QPixmap &pix);
    QPixmap to_image(QByteArray array);
public:
    database();
    ~database();
    void insert(QString tit,QPixmap px);
    QVector <std::tuple<QString,QPixmap>> get_records();
};

#endif // DATABASE_H
