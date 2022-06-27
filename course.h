#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include <bits/stdc++.h>
#include <QDataStream>
#include <QDate>
using namespace std;

class course
{
public:
    string courseName;
    int dd;
    QTime startTime;
    string classroom;
    string teacherName;
    course();
    course(string,int,QTime,string classroom_="",string teacher="");

};

#endif // COURSE_H
