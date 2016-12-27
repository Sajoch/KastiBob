#-------------------------------------------------
#
# Project created by QtCreator 2016-10-31T13:57:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guii
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    healer.cpp \
    alerts.cpp \
    cavebot.cpp \
    trainer.cpp \
    ../../running_inject/src/main.cpp \
    ../../running_inject/src/objectfile.cpp \
    ../../running_inject/src/remoteCode_string.cpp \
    ../../running_inject/src/remoteCode.c

HEADERS  += mainwindow.h \
    healer.h \
    alerts.h \
    cavebot.h \
    trainer.h \
    ../../running_inject/src/objectfile.hpp

FORMS    += mainwindow.ui \
    healer.ui \
    alerts.ui \
    cavebot.ui \
    trainer.ui
