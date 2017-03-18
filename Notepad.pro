#-------------------------------------------------
#
# Project created by QtCreator 2016-08-30T11:42:03
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Notepad
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mylabel.cpp

HEADERS  += mainwindow.h \
    mylabel.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
