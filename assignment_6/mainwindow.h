#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 Να γραφεί πρόγραμμα που θα αποθηκεύει σε ένα πίνακα τα στοιχεία μιας εταιρίες όνομα τμήματος
 και να εμφανίζει το μέσο μισθό με κουμπί,τις μέσες πωλήσεις του τμήματος όπως και τον υπάλληλο με τις περισσότερες πωλήσεις.
 Το πρόγραμμα να έχει την δινατότητα να αποθηκεύει τον πίνακα σε μορφή png και να μπορεί να εμφανίζει σε γράφημα (piechart) τις μέσες πωλήσεις
 κάθε τμήματος.
 */

#include <QMainWindow>
#include <QVBoxLayout>
#include <QTextStream>
#include <QFileDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChartView>

using namespace QtCharts;

struct employee
{
    QString name;
    int nsales;
    double salary;
};

class department
{
private:
    QString depname;
    QVector <employee> employees;
public:
    department(QString dn):depname(dn) {}
    void add_employee(const employee &e) {employees.append(e);}
    QString get_dep_name()const {return this->depname;}
    employee get_employee(int i)const {return this->employees.at(i);}
    double average_sales()
    {
        int sum=0;
        for(auto &x:this->employees)
        {
           sum+=x.nsales;
        }
        return (double)sum/this->employees.size();
    }
    double average_salary()
    {
        double avg=0.0;
        for(auto &x:this->employees)
        {
            avg+=x.salary;
        }
        return avg/this->employees.size();
    }
    QString to_string_md()
    {
        QString str="DEPARTMENT NAME:"+this->depname+"\n<ul>\n";
        for(auto &x:this->employees)
        {
            str+="<li><p style=color:red font-family:calibri>NAME:"+x.name+"\tSALES:"+QString::number(x.nsales)+"\tSALARY:"+QString::number(x.salary)+"</p></li>\n";
        }
        str+="</ul>";
        return str;
    }
    QString to_string()
    {
        QString str="DEPARTMENT NAME:"+this->depname+"\n";
        for(auto &x:this->employees)
        {
            str+="NAME:"+x.name+"\tSALES:"+QString::number(x.nsales)+"\tSALARY:"+QString::number(x.salary)+"\n";
        }
        return str;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *mw;
    QVBoxLayout *ml;
    QTableWidget *tab;
    QVector <department> deps;
    QChart *chart;
    QPieSeries *series;
    QChartView *view;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void loadslot();
    void exportpng();
    void saveslot();
    void showslot();
    void averagesal();
    void averagesalesslot();
    void showempsslot();
};
#endif // MAINWINDOW_H
