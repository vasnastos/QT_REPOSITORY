#ifndef UPLOADSONG_H
#define UPLOADSONG_H
#include <QDialog>
#include <QObject>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMediaPlaylist>
#include <QLabel>

class uploadsong:public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *mainlayout;
    QLineEdit *songname;
    QLabel *preview;
public:
    uploadsong(QStringList &names,QMediaPlaylist &pl,QWidget *parent=nullptr);
};

#endif // UPLOADSONG_H
