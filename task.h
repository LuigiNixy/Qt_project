#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <bits/stdc++.h>
#include <QDataStream>
#include <QDate>
using namespace std;

class task:public QObject
{
public:
    task(string,int,int ,int ,int ,int );
    task();
    task(char*);
    task(char*,int ,int ,int,int,int);
    task(string,QDate,QTime,int t=0);
    void setAlarm(bool);
    bool isAlarm;
    string taskName;
    QDate ddl_date;
    QTime ddl_time;

    int period;
    int repeated_times;

    friend bool operator <(task a,task b){
        if(a.ddl_date==b.ddl_date) return a.ddl_time<b.ddl_time;
        else return a.ddl_date<b.ddl_date;
    };

};

#endif // TASK_H
