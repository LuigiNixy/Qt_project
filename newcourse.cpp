#include "newcourse.h"
#include "ui_newcourse.h"
#include <qmessagebox.h>
#include <qt_window.h>
#include <QDebug>

using namespace std;
newCourse::newCourse(QWidget *parent,int x,int y) :
    QDialog(parent),
    ui(new Ui::newCourse)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("新建课程"));
    if(x!=-1&&y!=-1){
        ui->Dates->setCurrentIndex(y);
        ui->startTime->setTime(QTime(x+6,0));
        ui->endTime->setTime(QTime(x+7,0));
    }
    ui->startTime->setMinimumTime(QTime::fromString("6:00","h:mm"));
    ui->endTime->setMinimumTime(QTime::fromString("6:00","h:mm"));
    connect(ui->courseCancel,&QPushButton::clicked,this,[=](){
       this->close();

    });
    connect(ui->startTime,&QTimeEdit::timeChanged,ui->endTime,[=](){
        ui->endTime->setMinimumTime(ui->startTime->time().addSecs(3600));
        ui->endTime->setTime(ui->startTime->time());
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

        QTime startTime = ui->startTime->time();
        QTime endTime = ui->endTime->time();

       Qt_window * prt= (Qt_window*) parentWidget();

        course* tmp = new course(courseName.toStdString(),courseDate,startTime,endTime,classroom.toStdString(),teacherName.toStdString());
       prt->todoCourse.push(tmp);

       prt->addCourse(tmp);

       this->close();

    });

}

newCourse::~newCourse()
{
    delete ui;
}
