#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QComboBox>
#include <QDesktopWidget>
#include <QPixmap>
#include <QLabel>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTabWidget>
#include <QPushButton>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidget>

class student
{
private:
    int id;
    QString fullname;
    QString lname;
    double grade;
public:
    student(int i,QString fn,QString ln,double gr):id(i),fullname(fn),lname(ln),grade(gr) {}
    int get_id()const {return this->id;}
    QString get_fullname()const {return this->fullname;}
    QString get_lname()const {return this->lname;}
    double get_grade()const {return this->grade;}
    QString to_str()
    {
        return QString::number(this->id)+"--"+this->fullname+"--"+this->lname+"--"+QString::number(this->grade);
    }
};

QString read_copyright();

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QComboBox *cb;
    QTextEdit *ed;
    QTabWidget *tw;
    void tab1();
    void tab2();
    QVector <student> students;
    QVector <QString> lessons;
    QTableWidget *tab;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void get_lessons();
    bool lesson_is_in(const student &s);
public slots:
    void loadslot();
    void saveslot();
    void exportslot();
    void comboslot(QString x);
};
#endif // MAINWINDOW_H
