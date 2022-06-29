#include "mylistwidgetitem.h"
#include "qlistwidget.h"
#include <QDate>
#include <QTime>
#include <QList>
#include <Qt>
using namespace std;
myListWidgetItem::myListWidgetItem()
{

}

myListWidgetItem::myListWidgetItem(string name_, QDateTime time_){
    setTextAlignment(Qt::AlignAbsolute);
    taskName = name_;
    taskTime = time_;
}


bool myListWidgetItem::operator <(const QListWidgetItem &other)const{
    QDateTime a,b;
    a = this->data(Qt::UserRole).toDateTime();
    b = other.data(Qt::UserRole).toDateTime();
    return a<b;

}
