#ifndef TIMEEDIE_H
#define TIMEEDIE_H

#include <QDialog>
#include <QDateTimeEdit>

namespace Ui {
class timeEdie;
}

class timeEdie : public QDialog
{
    Q_OBJECT

public:
    explicit timeEdie(QDateTime setDt,QWidget *parent = 0);
    ~timeEdie();
signals:
    void sendData(QDateTime);
private:
    Ui::timeEdie *ui;
};

#endif // TIMEEDIE_H
