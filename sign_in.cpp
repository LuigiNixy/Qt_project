#include "sign_in.h"
#include "ui_sign_in.h"
#include <qt_window.h>
#include <QDebug>
#include <QTWidgets>
#include <QFrame>
#include <QLabel>
#include <QMessageBox>
#include <qdebug.h>
#include <QImage>
#include <QTableWidgetItem>
#include <QPalette>
#include <QtGui>
#include <qsettings.h>
#include <QPushButton>
#include <QDate>
#include <QTimer>
using namespace std;

sign_in::sign_in(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sign_in)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);
    this->resize(1100,1100);
//    QWidget* widget = new QWidget(this);
    ui->widget->resize(1500,1500);
    QString date = QDate::currentDate().toString("d");//几日
    QString day = QDate::currentDate().toString("dddd");//星期几
    QString year = QDate::currentDate().toString("yyyy");//年份
    QString month = QDate::currentDate().toString("M");//几月
    ui->widget->setWindowTitle(tr("每日签到"));
    ui->label = new QLabel(this);
    ui->label->setText("                   今天是"+year+"年"+month+"月"+date+"日"+day+"，你已经成功打卡，要注意最近的ddl并好好上课哟~");
    ui->label->setAlignment(Qt::AlignVCenter);
    ui->label->resize(900,60);
    ui->widget->setAutoFillBackground(true);
    QPalette palette;
    QString url = ":/sign_in_image/"+date+".jpg";
    palette.setBrush(QPalette::Background,QBrush(QPixmap(url)));
    // sprintf(buf,"border-image:url(:/new/prefix1/photo/%d.jpg)",index);
    ui->widget->setPalette(palette);

//    widget->setStyleSheet("border-image:url(:/sign_in_image/2.jpg)))");

    myTimer->start(3000);
    connect(myTimer,SIGNAL(timeout()),this,SLOT(close()));
}

//void sign_in::windowClose(){
//    this->close();
//    return;
//}

sign_in::~sign_in()
{
    delete ui;
}
