#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QVBoxLayout>
#include "database.h"
#include <QLabel>
#include <QPushButton>
#include <QObject>
class dialog:public QDialog
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *lay;
    database *db;
    QLineEdit *username,*password;
    QPushButton *log,*cancel;
    bool cancelbutton;
public:
    dialog(database &getdb);
    ~dialog();
    bool enablecancelbutton();
public slots:
    void checkcredentials();
    void cancelslot();
};

#endif // DIALOG_H
