#-------------------------------------------------
#
# Project created by QtCreator 2022-05-11T10:20:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_project
TEMPLATE = app


SOURCES += main.cpp\
        qt_window.cpp \
    task.cpp \
    newtask.cpp \
    newcourse.cpp \
    course.cpp \
    mylistwidgetitem.cpp \
    timeedie.cpp \
    sign_in.cpp \
    sign_up_dialog.cpp

HEADERS  += qt_window.h \
    task.h \
    newtask.h \
    newcourse.h \
    course.h \
    mylistwidgetitem.h \
    timeedie.h \
    sign_in.h \
    sign_up_dialog.h

FORMS    += qt_window.ui \
    newtask.ui \
    newcourse.ui \
    timeedie.ui \
    sign_in.ui \
    sign_up_dialog.ui

RESOURCES += \
    sign_in_image.qrc
