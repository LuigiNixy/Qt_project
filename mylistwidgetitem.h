#ifndef MYLISTWIDGETITEM_H
#define MYLISTWIDGETITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QListWidget>
#include <QDate>
#include <QDateTime>
#include <QTime>
using namespace std;
class myListWidgetItem : public QListWidgetItem
{
public:
    string taskName;
    QDateTime taskTime;
    myListWidgetItem();
    myListWidgetItem(string name_,QDateTime time_);
    bool operator <(const QListWidgetItem &other) const;
    bool isTask;
};

#endif // MYLISTWIDGETITEM_H
