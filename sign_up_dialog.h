#ifndef SIGN_UP_DIALOG_H
#define SIGN_UP_DIALOG_H

#include <QDialog>

namespace Ui {
class sign_up_dialog;
}

class sign_up_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit sign_up_dialog(QWidget *parent = 0);
    ~sign_up_dialog();


private:
    Ui::sign_up_dialog *ui;
private slots:
    void on_actionSign_in_triggered();

};

#endif // SIGN_UP_DIALOG_H
