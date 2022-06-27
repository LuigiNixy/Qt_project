#include "qt_window.h"
#include "ui_qt_window.h"
#include "newtask.h"
#include "newcourse.h"
#include <QMessageBox>
#include <qdebug.h>
#include <QDebug>
#include <QTableWidgetItem>
#include <qsettings.h>
#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

Qt_window::Qt_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qt_window)
{
    ui->setupUi(this);
//    QPushButton *btn = /*new QPushButton("todo list",this);
//    resize(600,400);
//    setWindowTitle("test");*/
    SetMyAppAutoRun(1);

    //设置表格

    date2num["Mon"]=1;
    date2num["Tue"]=2;
    date2num["Wed"]=3;
    date2num["Thu"]=4;
    date2num["Fri"]=5;
    date2num["Sat"]=6;
    date2num["Sun"]=7;
    QDate curDate = QDate::currentDate();
    QDate da[8];
    QLocale locale = QLocale::English;
    for(int i=1;i<=7;i++)
        da[i]=curDate.addDays(i-date2num[locale.toString(curDate,"ddd")]);
//    for(int i=1;i<=7;i++)
//        qDebug() <<"today"<<locale.toString(da[i],"ddd")<<endl;
    QString curDateString = QDate::currentDate().toString("MM/dd");
    ui->schedule->setColumnCount(7);
    ui->schedule->setHorizontalHeaderLabels(QStringList()<<locale.toString(da[1],"ddd\nMM/dd")<<locale.toString(da[2],"ddd\nMM/dd")
            <<locale.toString(da[3],"ddd\nMM/dd")<<locale.toString(da[4],"ddd\nMM/dd")<<locale.toString(da[5],"ddd\nMM/dd")<<locale.toString(da[6],"ddd\nMM/dd")
            <<locale.toString(da[7],"ddd\nMM/dd"));
    ui->schedule->setRowCount(17);
    ui->schedule->setVerticalHeaderLabels(QStringList()<<"  6:00-7:00"<<"  7:00-8:00"
                                          <<"  8:00-9:00"<<"  9:00-10:00"<<"  10:00-11:00"<<"  11:00-12:00"<<"  12:00-13:00"<<"  13:00-14:00"<<"  14:00-15:00"<<"  15:00-16:00"<<"  16:00-17:00"
                                          <<"  17:00-18:00"<<"  18:00-19:00"<<"  19:00-20:00"<<"  20:00-21:00"<<"  21:00-22:00"<<"  22:00-23:00");
    //如下代码设置横向表格头的间隔线，有四个方向的间隔线,不需要间隔线的可以设置为0px
    ui->schedule->horizontalHeader()->setStyleSheet(
    "QHeaderView::section{"
                "border-top:0.5px solid #E5E5E5;"
                "border-left:0px solid #E5E5E5;"
                "border-right:0.5px solid #E5E5E5;"
                "border-bottom: 0.5px solid #E5E5E5;"
                "background-color:white;"
                "padding:4px;"
            "}"
    );

    //如下代码设置横向表格头的间隔线，有四个方向的间隔线,不需要间隔线的可以设置为0px
    ui->schedule->verticalHeader()->setStyleSheet(
    "QHeaderView::section{"
                "border-top:1px solid #E5E5E5;"
                "border-left:1px solid #E5E5E5;"
                "border-right:1px solid #E5E5E5;"
                "border-bottom: 1px solid #E5E5E5;"
                "background-color:white;"
                "padding:4px;"
            "}"
    );



//    connect(ui->pushButton,&QPushButton::clicked,this,&Qwidget)
    //新建任务
    connect(ui->actionNew_task,&QAction::triggered,this,[=](){
    Qt::WindowFlags flags = Qt::Dialog;
        newTask *newtask = new newTask(this);
        newtask->setWindowFlags(flags);
        newtask->show();

    });

    //新建课程
    connect(ui->actionNew_course,&QAction::triggered,this,[=](){
        Qt::WindowFlags flags = Qt::Dialog;
        newCourse *newcourse = new newCourse(this);
        newcourse->setWindowFlags(flags);
        newcourse->show();

    });

    connect(ui->schedule,&QTableWidget::doubleClicked,this,[=](){
        Qt::WindowFlags flags = Qt::Dialog;
        newCourse *newcourse = new newCourse(this);
        newcourse->setWindowFlags(flags);
        newcourse->show();
    });

//    connect(ui->)

    //动态更新时间
    myTimer=new QTimer(this);
    myTimer->start(1000);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(getDateTime()));

}

Qt_window::~Qt_window()
{
    delete ui;
}

void Qt_window::addTask(task* t){

    ui->taskList->addItem(QString::fromStdString(t->taskName));
//    qDebug()<<" "<<t->ddl_date.toString()<<" "<<t->ddl_time.toString()<<endl;
    return;
}

void Qt_window::addCourse(course * t){
    int x = t->dd;

    for(int y = t->startTime.hour();y<=t->endTime.hour()-1;y++)
    ui->schedule->setItem(y-6,x,new QTableWidgetItem(QString::fromStdString(t->courseName+"\n"+t->classroom+
                                                                                           "\n"+t->teacherName)));


}

void Qt_window::getDateTime(){
    QString curTime = QTime::currentTime().toString();
    QString curDate = QDate::currentDate().toString();
//    qDebug() <<curTime<<endl;
    if(todoTask.empty()) return;
    task* tmp = todoTask.top();
    if(tmp==NULL) return;
//    qDebug() <<tmp->ddl_date<<endl;
    if(curDate!=tmp->ddl_date.toString()) return;
//    qDebug() <<tmp->ddl_time<<endl;
    if(curTime!=tmp->ddl_time.toString()) return;
    qDebug() <<"ddl"<<endl;
    QMessageBox::warning(this,QString::fromStdString("快到DDL了!"),QString::fromStdString("快到DDL了！！！"));
    if(tmp->repeated_times==0){
        Qt_window *ptr = (Qt_window* ) parentWidget();
        ptr->todoTask.pop();
    }
    else{
        tmp->repeated_times--;

    }
}

void Qt_window::SetMyAppAutoRun(bool isstart)

{
     QString application_name = QApplication::applicationName();
     QSettings *settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);
     if(isstart){
         QString application_path = QApplication::applicationFilePath();
         settings->setValue(application_name, application_path.replace("/", "\\"));
     }
     else settings->remove(application_name);
}


