#include "newtask.h"
#include "ui_newtask.h"
#include <QDebug>
#include <qt_window.h>
#include <QMessageBox>
#include <task.h>
using namespace std;
newTask::newTask(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newTask)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("新建任务"));
    ui->dateTimeEdit->setMinimumDate(QDate::currentDate());
    ui->dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
    ui->dateTimeEdit->setMinimumDateTime(QDateTime(QDate::currentDate(),
                                                   QTime::currentTime()));
    ui->dateTimeEdit->setTime(QTime::currentTime());
    ui->calendarWidget->setMinimumDate(QDate::currentDate());
    ui->calendarWidget->setMaximumDate(QDate::currentDate().addDays(365));
    //取消按钮
    connect(ui->taskCancel,&QPushButton::clicked,this,[=](){
        this->close();
    });
    ui->delayDays->setText(QString::fromStdString("0"));
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
        QString period = ui->delayDays->text();
        string tmp = period.toStdString();
        for(int i=0;i<tmp.length();i++)
                if(tmp[i]<'0'||tmp[i]>'9'){
                    QMessageBox::warning(this,QString::fromStdString("Error"),QString::fromStdString("请输入数字"));
                    return;
                }
        int p=period.toInt();

        if(task_Name=="") {
            //warning
            QMessageBox::warning(this,QString::fromStdString("Error"),QString::fromStdString("名字不能为空！"));
            return;
        }
        if(p>365||p<0){
            QMessageBox::warning(this,QString::fromStdString("Error"),QString::fromStdString("数字应当在0~365之间"));
            return;
        }
//        QTime ddl_time = ui->timeEdit->time();
        QDate calenderDate = ui->calendarWidget->selectedDate();
        QTime ddl_time_ = ui->dateTimeEdit->time();

//输入问题处理
        //增加任务到todoList
    Qt_window * prt= (Qt_window*) parentWidget();
        task * newTask = new task(task_Name.toStdString(),calenderDate,ddl_time_,p);

        prt->todoTask.push(newTask);

        prt->addTask(newTask);

        this->close();


    });
}

newTask::~newTask()
{
    delete ui;
}
