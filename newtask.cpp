#include "newtask.h"
#include "ui_newtask.h"
#include <QDebug>
#include <qt_window.h>
#include <QMessageBox>
using namespace std;
newTask::newTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newTask)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
    ui->calendarWidget->setMinimumDate(QDate::currentDate());
    ui->calendarWidget->setMaximumDate(QDate::currentDate().addDays(365));
    //取消按钮
    connect(ui->taskCancel,&QPushButton::clicked,this,[=](){
        this->close();
    });

    //日期设置
    connect(ui->calendarWidget,&QCalendarWidget::selectionChanged,ui->dateTimeEdit,[=](){
       QDate curDate=ui->calendarWidget->selectedDate();
       ui->dateTimeEdit->setDate(curDate);
    });


    connect(ui->dateTimeEdit,&QDateTimeEdit::dateChanged,ui->calendarWidget,[=](){
       QDate curDate=ui->dateTimeEdit->date();
       ui->calendarWidget->setSelectedDate(curDate);
    });


    //创建任务
    connect(ui->taskCreate,&QPushButton::clicked,this,[=](){
        QString task_Name = ui->lineEdit->text();
        if(task_Name=="") {
            //warning
            QMessageBox::warning(this,QString::fromStdString("Error"),QString::fromStdString("名字不能为空！"));
            return;
        }
//        QTime ddl_time = ui->timeEdit->time();
        QDate calenderDate = ui->calendarWidget->selectedDate();
        QTime ddl_time_ = ui->dateTimeEdit->time();

//输入问题处理
        //增加任务到todoList
    Qt_window * prt= (Qt_window*) parentWidget();


        prt->todoTask.push(new task(task_Name.toStdString(),calenderDate,ddl_time_));

        prt->addTask((prt->todoTask.top()));

        this->close();


    });
}

newTask::~newTask()
{
    delete ui;
}
