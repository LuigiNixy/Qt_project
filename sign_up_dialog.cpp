#include "sign_up_dialog.h"
#include "ui_sign_up_dialog.h"
#include <qt_window.h>
#include <QDebug>
#include <QTWidgets>
#include <QFrame>
#include <QLabel>
#include <QMessageBox>
#include <qdebug.h>
#include <QTableWidgetItem>
#include <qsettings.h>
#include <QPushButton>
using namespace std;


sign_up_dialog::sign_up_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign_up_dialog)
{
    ui->setupUi(this);
}

sign_up_dialog::~sign_up_dialog()
{
    delete ui;
}

void sign_up_dialog::on_actionSign_in_triggered(){
    QWidget* widget = new QWidget();
    QString date = QDate::currentDate().toString("d");
    QString day = QDate::currentDate().toString("dddd");//星期几
    QString year = QDate::currentDate().toString("yyyy");//年份
    QString month = QDate::currentDate().toString("M");
    widget->setWindowTitle(QObject::tr("每日签到"));
    QLabel * lable = new QLabel(widget);
//    lable->setText(QObject::tr(qDebug()<<"今天是"<<year<<"年"<<month<<"月"<<date<<"日"<<"dddd"<<"你已经成功打卡，要注意最近的ddl并且好好上课哟~"));
    widget->show();
}
