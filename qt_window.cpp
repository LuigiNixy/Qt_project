#include "qt_window.h"
#include "ui_qt_window.h"
#include "newtask.h"
#include <QMessageBox>
#include <qdebug.h>
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
    ui->schedule->setColumnCount(7);
    ui->schedule->setHorizontalHeaderLabels(QStringList()<<"Mon"<<"Tue"<<"Wed"<<"Thu"<<"Fri"<<"Sat"<<"Son");
    ui->schedule->setRowCount(15);
//    ui->schedule->setRowHeight();
    ui->schedule->setVerticalHeaderLabels(QStringList()<<"8:00-9:00"<<"9:00-10:00"<<"10:00-11:00"<<"11:00-12:00"<<"12:00-13:00"<<"13:00-14:00"<<"14:00-15:00"<<"15:00-16:00"<<"16:00-17:00"
                                          <<"17:00-18:00"<<"18:00-19:00"<<"19:00-20:00"<<"20:00-21:00"<<"21:00-22:00"<<"22:00-23:00");
//    ui->schedule->resize();

//    connect(ui->pushButton,&QPushButton::clicked,this,&Qwidget)
    //新建任务
    connect(ui->actionNew_task,&QAction::triggered,this,[=](){
    Qt::WindowFlags flags = Qt::Dialog;
        newTask *newtask = new newTask(this);
        newtask->setWindowFlags(flags);
        newtask->show();

    });

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
//    qDebug() <<"ddl"<<endl;
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
