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
    newtask.cpp

HEADERS  += qt_window.h \
    task.h \
    newtask.h

FORMS    += qt_window.ui \
    newtask.ui
