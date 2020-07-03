#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
# include <QPushButton>
# include <QLineEdit>
# include <QVBoxLayout>
# include <QHBoxLayout>
# include <QMessageBox>
# include <database.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Database *mydb;
    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
    QLineEdit *studentNameEdit,*studentLastnameEdit,*studentIdEdit;
    QLineEdit *lessonNameEdit,*lessonIdEdit,*lessonSemesterEdit;
    QLineEdit *enrollSidEdit,*enrollLidEdit;
    QPushButton *addStudentButton,*showStudentButton,*deleteStudentButton;
    QPushButton *addLessonButton,*showLessonsButton,*deleteLessonButton;
    QPushButton *addEnrollButton,*showEnrollButton,*deleteEnrollButton;
public slots:
    void addStudentSlot();
    void showStudentsSlot();
    void deleteStudentSlot();
    void addLessonSlot();
    void showLessonsSlot();
    void deleteLessonSlot();
    void addEnrollSlot();
    void showEnrollSlot();
    void deleteEnrollSlot();
};
#endif // MAINWINDOW_H
