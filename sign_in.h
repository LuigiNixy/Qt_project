#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
namespace Ui {
class sign_in;
}

class sign_in : public QWidget
{
    Q_OBJECT

public:
    explicit sign_in(QWidget *parent = 0);
    ~sign_in();
    QTimer * myTimer;
private:
    Ui::sign_in *ui;
//private slots:
//    void windowClose();
};

#endif // SIGN_IN_H
