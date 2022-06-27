#ifndef NEWCOURSE_H
#define NEWCOURSE_H

#include <QDialog>
using namespace std;
namespace Ui {
class newCourse;
}

class newCourse : public QDialog
{
    Q_OBJECT

public:
    explicit newCourse(QWidget *parent = 0);
    ~newCourse();

private:
    Ui::newCourse *ui;
};

#endif // NEWCOURSE_H
