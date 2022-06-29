#include "task.h"

task::task()
{
}


void task::setAlarm(bool t){
    isAlarm=t;
}

task::task(string Name_, QDate date_, QTime time_,int t){
    taskName= Name_;
    ddl_date =date_;
    ddl_time =time_;
    setAlarm(1);
    period=t;

}/*
bool task::operator <(task a,task b)*/

