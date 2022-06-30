#include "timeedie.h"
#include "ui_timeedie.h"
#include <QDateTimeEdit>
timeEdie::timeEdie(QDateTime setDt,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::timeEdie)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(setDt);

    connect(ui->Done,&QPushButton::clicked,this,[=](){
        QDateTime tmp = ui->dateTimeEdit->dateTime();
        emit sendData(tmp);
        this->close();
    });

    connect(ui->Canc,&QPushButton::clicked,this,[=](){
        this->close();
    });
}

timeEdie::~timeEdie()
{
    delete ui;
}
