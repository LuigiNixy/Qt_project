#include "newcourse.h"
#include "ui_newcourse.h"
#include <qmessagebox.h>
#include <qt_window.h>
#include <QDebug>

using namespace std;
newCourse::newCourse(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newCourse)
{
    ui->setupUi(this);
    ui->courseTime->setMinimumTime(QTime::fromString("6:00","h:mm"));
    connect(ui->courseCancel,&QPushButton::clicked,this,[=](){
       this->close();

    });

    connect(ui->courseCreate,&QPushButton::clicked,this,[=](){

        QString courseName = ui->lineEdit->text();
        if(courseName==""){
            QMessageBox::warning(this,QString::fromStdString("Error"),QString::fromStdString("名字不能为空！"));
            return;
        }
        QString classroom = ui->lineEdit_2->text();
        QString teacherName = ui->lineEdit_3->text();


        int courseDate = ui->Dates->currentIndex();
        qDebug()<<courseDate<<endl;
        QTime courseTime = ui->courseTime->time();

       Qt_window * prt= (Qt_window*) parentWidget();


       prt->todoCourse.push(new course(courseName.toStdString(),courseDate,courseTime));

       prt->addCourse((prt->todoCourse.top()));

       this->close();

    });






}

newCourse::~newCourse()
{
    delete ui;
}
