#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T20:30:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kastibobgui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    healer.cpp \
    runemaker.cpp \
    hotheys.cpp

HEADERS  += mainwindow.h \
    healer.h \
    runemaker.h \
    hotheys.h

FORMS    += mainwindow.ui \
    healer.ui \
    runemaker.ui \
    hotheys.ui
