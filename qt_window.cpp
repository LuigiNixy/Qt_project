#include "qt_window.h"
#include "ui_qt_window.h"
#include "newtask.h"
#include "newcourse.h"
#include <sign_in.h>
#include <newcourse.h>
#include "qlistwidget.h"
#include <QMessageBox>
#include <qdebug.h>
#include <QDebug>
#include <QTableWidgetItem>
#include <Qt>
#include <QDateTime>
#include <QMenu>
#include <qsettings.h>
#include <mylistwidgetitem.h>
#include <timeedie.h>
#include <QColor>
#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

Qt_window::Qt_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Qt_window)
{
    ui->setupUi(this);
    sign_in * t = new sign_in(this);
    Qt::WindowFlags flagT = Qt::Dialog;
    t->setWindowFlags(flagT);
    t->show();

//    QTimer::singleShot(3000,t,SLOT(close()));
//    ui->setupUi(this);
//    QPushButton *btn = /*new QPushButton("todo list",this);
//    resize(600,400);
//    setWindowTitle("test");*/
    SetMyAppAutoRun(1);
//    ui->centralWidget->setStyleSheet("background-color:#F5F5F5;");
    //设置表格
    ui->schedule->setContextMenuPolicy(Qt::CustomContextMenu);


    ui->taskList->setSortingEnabled(true);
    ui->taskList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->schedule->setStyleSheet("\
                                QTableWidget{\
                                color:#DCDCDC;\
                                background:#E1FFFF;\
                                border:1px solid #87CEEB;\
                                gridline-color:#87CEEB;\
                                border-radius:10px;\
                                }\
                                QTableWidget::item:selected{\
                                color:#DCDCDC;\
                                background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F5FFFA,stop:1 #F5FFFA);\
                                font:bold;color:black;\
                                }\
                                QTableWidget::item:hover{\
                                background:#FFFFE0;\
                                }\
\
                                QHeaderView::section{\
                                text-align:center;\
                                background:#5E5E5E;\
                                padding:3px;\
                                margin:0px;\
                                color:#DCDCDC;\
                                border:1px solid #242424;\
                                border-left-width:0;\
                                }\
");
    ui->taskList->setStyleSheet("\
                                QListWidget{"
                                            "color:#D2FFE3;\
                                            background:#E1FFFF;\
                                            border:1px solid #87CEEB;\
                                            gridline-color:#87CEEB;\
                                            }\
QListWidget::item{\
font:bold;color:black;font-famliy:'Microsoft YaHei UI';}\
                                              \
                                 QListWidget::item:selected{\
                                    color:#DCDCDC;\
                                    background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #F5FFFA,stop:1 #F5FFFA);\
                                    font:bold;color:black;\
                                     border-radius:10px;\
                                    }\
                                    QListWidget::item:hover{\
                                    background:#FFFFE0;\
                                    }\
\
                                ");

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

    ui->schedule->horizontalHeader()->setStyleSheet(
    "QHeaderView::section{"
                "border-top:0.5px solid #E5E5E5;"
                "border-left:0px solid #E5E5E5;"
                "border-right:0.5px solid #E5E5E5;"
                "border-bottom: 0.5px solid #E5E5E5;"
                "background-color:#3A5BA0;"
                "padding:4px;"
            "}"
    );


    ui->schedule->verticalHeader()->setStyleSheet(
    "QHeaderView::section{"
                "border-top:1px solid #E5E5E5;"
                "border-left:1px solid #E5E5E5;"
                "border-right:1px solid #E5E5E5;"
                "border-bottom: 1px solid #E5E5E5;"
                "background-color:#3A5BA0;"
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

    connect(ui->schedule,&QTableWidget::cellDoubleClicked,this,[=](int row,int column){
        Qt::WindowFlags flags = Qt::Dialog;
        newCourse *newcourse = new newCourse(this,row,column);
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
    ui->taskList->setSortingEnabled(true);

    myListWidgetItem *item = new myListWidgetItem(t->taskName,QDateTime(t->ddl_date,t->ddl_time));
    item->setText(QString::fromStdString(t->taskName+" "+t->ddl_date.toString("yyyy年MM月dd日").toStdString()+" "+t->ddl_time.toString().toStdString()));
    item->setData(Qt::UserRole,QDateTime(t->ddl_date,t->ddl_time));

    ui->taskList->addItem(item);
//    qDebug()<<" "<<(item->taskTime<ui->taskList->item(1)->data(<<endl;
    ui->taskList->sortItems();

//    qDebug()<<" "<<t->ddl_date.toString()<<" "<<t->ddl_time.toString()<<endl;
    return;
}

void Qt_window::addCourse(course * t){
    int x = t->dd;

    for(int y = t->startTime.hour();y<=t->endTime.hour()-1;y++)
    {
        ui->schedule->setItem(y-6,x,new QTableWidgetItem(QString::fromStdString(t->courseName+" "+t->classroom+
                                                                                               " "+t->teacherName)));
        ui->schedule->item(y-6,x)->setTextAlignment(Qt::AlignCenter);
        ui->schedule->item(y-6,x)->setBackgroundColor(QColor(QTime::currentTime().minute()*3+QTime::currentTime().msec()/20,
                                                          QTime::currentTime().msec()/5,
                                                          QTime::currentTime().second()*4));
    }



}

void Qt_window::getDateTime(){
    QString curTime = QTime::currentTime().toString();
    QString curDate = QDate::currentDate().toString();
//    qDebug() <<curTime<<endl;
    if(todoTask.empty()) return;
    task* tmp_ = todoTask.top();
    if(tmp_==NULL) return;
    QListWidgetItem  *tmp = ui->taskList->item(0);
    if(tmp==NULL) return;
    if(tmp->data(Qt::UserRole).toDateTime()<QDateTime::currentDateTime()){
        if(tmp_->period==0){
            ui->taskList->removeItemWidget(ui->taskList->item(0));
//            todoTask.pop();
        }
        else{
            myListWidgetItem * item = new myListWidgetItem(tmp_->taskName,QDateTime(tmp_->ddl_date.addDays(tmp_->period),tmp_->ddl_time));

            ui->taskList->removeItemWidget(ui->taskList->item(0));
            ui->taskList->addItem(item);
//             todoTask.pop();
             ui->taskList->sortItems();
//             delete item;
        }
        tmp = ui->taskList->item(0);

    }
    if(tmp==NULL) return;
    if(QDateTime(tmp_->ddl_date,tmp_->ddl_time)<tmp->data(Qt::UserRole).toDateTime()&&!todoTask.empty()&&tmp_!=NULL) {
        todoTask.pop();
        tmp_ = todoTask.top();

    }
    if(tmp_==NULL) return;
    if(tmp==NULL) return;
//    qDebug() <<tmp->ddl_date<<endl;
    if(curDate!=tmp->data(Qt::UserRole).toDateTime().date().toString()) return;
//    qDebug() <<tmp->ddl_time<<endl;
    if(curTime!=tmp->data(Qt::UserRole).toDateTime().time().toString()) return;
    qDebug() <<"ddl"<<endl;
    QMessageBox::warning(this,QString::fromStdString("快到DDL了!"),QString::fromStdString("快到DDL了！！！"));
    if(tmp_->period==0){
        ui->taskList->removeItemWidget(ui->taskList->item(0));
        todoTask.pop();
    }
    else{
        myListWidgetItem * item = new myListWidgetItem(tmp_->taskName,QDateTime(tmp_->ddl_date.addDays(tmp_->period),tmp_->ddl_time));

        ui->taskList->removeItemWidget(ui->taskList->item(0));
        ui->taskList->addItem(item);
         todoTask.pop();
         ui->taskList->sortItems();
         delete item;
    }

    delete tmp_;
    delete tmp;
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



void Qt_window::on_schedule_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    QAction *dlt = menu.addAction(tr("删除"));
    menu.addSeparator();
    QAction *edit = menu.addAction(tr("编辑"));
    menu.addSeparator();
    QAction *clear = menu.addAction(tr("清空"));

    connect(dlt,&QAction::triggered,this,[=](){
       QTableWidgetItem *item = ui->schedule->itemAt(pos);
       if(item==NULL) {
//           qDebug()<<"NULL"<<endl;
           return;
       }
       item->setText("");
       delete item;
    });

    connect(edit,&QAction::triggered,this,[=](){
        QTableWidgetItem *item =ui->schedule->itemAt(pos);
        if(item==NULL) {
//            qDebug()<<"NULL";
            return;
        }
        Qt::WindowFlags flags = Qt::Dialog;
        newCourse *newcourse = new newCourse(this,item->row(),item->column());
        newcourse->setWindowFlags(flags);
        newcourse->show();

        delete item;
    });

    connect(clear,&QAction::triggered,this,[=](){
        ui->schedule->clearContents();
    });

    menu.exec(QCursor::pos());
}

void Qt_window::on_taskList_customContextMenuRequested(const QPoint &pos)
{
    QMenu menu;
    QAction *dlt = menu.addAction(tr("删除"));
    menu.addSeparator();
    QAction *edit = menu.addAction(tr("更改时间"));
    menu.addSeparator();
    QAction *clean = menu.addAction(tr("清空"));

    connect(dlt,&QAction::triggered,this,[=](){
        QListWidgetItem *item = ui->taskList->itemAt(pos);
        if(item==NULL){
            return;
        }
        ui->taskList->removeItemWidget(item);
        delete item;
    });
    connect(edit,&QAction::triggered,this,[=](){
        QListWidgetItem *item =ui->taskList->itemAt(pos);
                if(item==NULL) {
                    return;
                }
                Qt::WindowFlags flags = Qt::Dialog;
                    newTask *newtask = new newTask(this);
                    newtask->setWindowFlags(flags);
                    newtask->show();
                delete item;
            });

    connect(clean,&QAction::triggered,this,[=](){
        ui->taskList->clear();
    });

    menu.exec(QCursor::pos());
}

void Qt_window::receiveDate(QDateTime tmp){
//    QListWidgetItem *item =ui->taskList->itemAt(pos);
//    item->setData(Qt::UserRole,tmp);
    return;
}

void Qt_window::widgetClose(){
    ui->setupUi(this);
}


