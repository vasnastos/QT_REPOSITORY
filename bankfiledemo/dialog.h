#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class dialog:public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *mainlayout;
    QLineEdit *number;
    QPushButton *but;
    QVector <QString> numbers;
    QString connectednumber;
    bool pressed;
public:
    dialog(QVector <QString> &accs);
    ~dialog();
    QString getconnect();
    bool forceclose();
public slots:
    void checknum();
    void cancelslot();
};

#endif // DIALOG_H
