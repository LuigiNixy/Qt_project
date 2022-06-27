#ifndef QT_WINDOW_H
#define QT_WINDOW_H

#include <QMainWindow>
#include <task.h>
#include <course.h>
#include <bits/stdc++.h>
#include <QTime>
#include <QTimer>
using namespace std;
namespace Ui {
class Qt_window;
}

class Qt_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Qt_window(QWidget *parent = 0);
    ~Qt_window();
    priority_queue<task*> todoTask;
    priority_queue<course* > todoCourse;
//    priority_queue<x>
    void addTask(task*);
    void addCourse(course*);
    QTimer *myTimer;
    void SetMyAppAutoRun(bool);
public slots:
    void getDateTime();



private:
    Ui::Qt_window *ui;
};

#endif // QT_WINDOW_H
