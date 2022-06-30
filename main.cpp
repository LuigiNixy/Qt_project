#include "qt_window.h"
#include "sign_in.h"
#include <QApplication>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    Qt_window w;
    w.show();

    return a.exec();
}
