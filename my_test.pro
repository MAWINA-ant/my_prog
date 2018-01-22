#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T12:21:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    keyboard.cpp \
    mouse.cpp \
    windowproc.cpp \
    mydatabase.cpp

HEADERS  += mainwindow.h \
    keyboard.h \
    mouse.h \
    windowproc.h \
    mydatabase.h

FORMS    += mainwindow.ui
