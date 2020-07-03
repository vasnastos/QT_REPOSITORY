#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800,300);
    setWindowTitle("Example");
    mainWidget=new QWidget;
    setCentralWidget(mainWidget);
    mainWidget->setFixedSize(this->width(),this->height());
    mainLayout=new QVBoxLayout;
    mainWidget->setLayout(mainLayout);
    mydb=new Database;

    QHBoxLayout *r1=new QHBoxLayout;
    studentIdEdit=new QLineEdit;
    studentIdEdit->setPlaceholderText("SID");
    r1->addWidget(studentIdEdit);
    studentNameEdit=new QLineEdit;
    studentNameEdit->setPlaceholderText("Name");
    r1->addWidget(studentNameEdit);
    studentLastnameEdit=new QLineEdit;
    studentLastnameEdit->setPlaceholderText("Lastname");
    r1->addWidget(studentLastnameEdit);
    addStudentButton=new QPushButton;
    addStudentButton->setText("ADD STUDENT");
    r1->addWidget(addStudentButton);
    connect(addStudentButton,SIGNAL(clicked(bool)),this,SLOT(addStudentSlot()));

    showStudentButton=new QPushButton("SHOW");
    r1->addWidget(showStudentButton);
    connect(showStudentButton,SIGNAL(clicked(bool)),this,SLOT(showStudentsSlot()));


    deleteStudentButton=new QPushButton;
    deleteStudentButton=new QPushButton("DELETE");
    r1->addWidget(deleteStudentButton);
    connect(deleteStudentButton,SIGNAL(clicked(bool)),this,SLOT(deleteStudentSlot()));
    mainLayout->addLayout(r1);

    QHBoxLayout *r2=new QHBoxLayout;
    lessonIdEdit=new QLineEdit;
    lessonIdEdit->setPlaceholderText("LESSONID");
    r2->addWidget(lessonIdEdit);
    lessonNameEdit=new QLineEdit;
    lessonNameEdit->setPlaceholderText("NAME");
    r2->addWidget(lessonNameEdit);
    lessonSemesterEdit=new QLineEdit;
    lessonSemesterEdit->setPlaceholderText("SEMESTER");
    r2->addWidget(lessonSemesterEdit);
    mainLayout->addLayout(r2);
    addLessonButton=new QPushButton;
    addLessonButton->setText("ADD LESSON");
    r2->addWidget(addLessonButton);
    connect(addLessonButton,SIGNAL(clicked(bool)),this,SLOT(addLessonSlot()));

    showLessonsButton=new QPushButton;
    showLessonsButton->setText("SHOW");
    r2->addWidget(showLessonsButton);
    connect(showLessonsButton,SIGNAL(clicked(bool)),this,SLOT(showLessonsSlot()));


    deleteLessonButton=new QPushButton;
    deleteLessonButton->setText("DELETE");
    r2->addWidget(deleteLessonButton);
    connect(deleteLessonButton,SIGNAL(clicked(bool)),this,SLOT(deleteLessonSlot()));


    QHBoxLayout *r3=new QHBoxLayout;
    enrollSidEdit=new QLineEdit;
    enrollSidEdit->setPlaceholderText("STUDENT ID");
    r3->addWidget(enrollSidEdit);
    enrollLidEdit=new QLineEdit;
    enrollLidEdit->setPlaceholderText("LESSON ID");
    r3->addWidget(enrollLidEdit);
    addEnrollButton=new QPushButton;
    addEnrollButton->setText("ADD ENROLL");
    r3->addWidget(addEnrollButton);
    connect(addEnrollButton,SIGNAL(clicked(bool)),this,SLOT(addEnrollSlot()));

    showEnrollButton=new QPushButton;
    showEnrollButton->setText("SHOW");
    r3->addWidget(showEnrollButton);
    connect(showEnrollButton,SIGNAL(clicked(bool)),this,SLOT(showEnrollSlot()));


    deleteEnrollButton=new QPushButton;
    deleteEnrollButton->setText("DELETE");
    r3->addWidget(deleteEnrollButton);
    connect(deleteEnrollButton,SIGNAL(clicked(bool)),this,SLOT(deleteEnrollSlot()));


    mainLayout->addLayout(r3);
}

void MainWindow::addStudentSlot()
{
    Student st(studentIdEdit->text().toInt(),studentNameEdit->text(),studentLastnameEdit->text());
    mydb->addStudent(st);
}

void MainWindow::showStudentsSlot()
{
    QString st="<ol>";
    QVector<Student> x=mydb->getStudents();

    for(int i=0;i<x.size();i++)
        st+="<li>"+x[i].toString()+"</li>";
    st+="</ol>";
    QMessageBox::information(this,"Info",st);
}

void MainWindow::deleteStudentSlot()
{
    Student st(studentIdEdit->text().toInt(),
               studentNameEdit->text(),studentLastnameEdit->text());
    mydb->deleteStudent(st);
}

void MainWindow::addLessonSlot()
{
    Lesson lt(lessonIdEdit->text().toInt(),lessonNameEdit->text(),
              lessonSemesterEdit->text().toInt());
    mydb->addLesson(lt);
}

void MainWindow::showLessonsSlot()
{
    QString st="<ol>";
    QVector<Lesson> x=mydb->getLessons();
    for(int i=0;i<x.size();i++)
        st+="<li>"+x[i].toString()+"</li>";
    st+="</ol>";
    QMessageBox::information(this,"Info",st);

}

void MainWindow::deleteLessonSlot()
{
    Lesson lt(lessonIdEdit->text().toInt(),lessonNameEdit->text(),
              lessonSemesterEdit->text().toInt());
    mydb->deleteLesson(lt);
}

void MainWindow::addEnrollSlot()
{
    Enroll lt(enrollSidEdit->text().toInt(),enrollLidEdit->text().toInt());
    mydb->addEnroll(lt);
}

void MainWindow::showEnrollSlot()
{
    QString st="<ol>";
    QVector<Enroll> x=mydb->getEnrolls();
    for(int i=0;i<x.size();i++)
        st+="<li>"+mydb->getstudentlastname(x.at(i).getStudentId())+"--"+mydb->getlessonname(x.at(i).getLessonId())+"</li>";
    st+="</ol>";
    QMessageBox::information(this,"Info",st);
}

void MainWindow::deleteEnrollSlot()
{
    Enroll lt(enrollSidEdit->text().toInt(),enrollLidEdit->text().toInt());
    mydb->deleteEnroll(lt);
}

MainWindow::~MainWindow()
{
    delete mydb;
}

