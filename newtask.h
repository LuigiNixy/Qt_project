#ifndef NEWTASK_H
#define NEWTASK_H

#include <QWidget>
#include <qt_window.h>
using namespace std;
namespace Ui {
class newTask;
}

class newTask : public QWidget
{
    Q_OBJECT

public:
    explicit newTask(QWidget *parent = 0);
    ~newTask();
friend class task;
friend class qt_window;
private:
    Ui::newTask *ui;
};

#endif // NEWTASK_H
