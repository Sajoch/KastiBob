#-------------------------------------------------
#
# Project created by QtCreator 2016-12-27T21:36:09
#
#-------------------------------------------------

QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KastiBobGui
TEMPLATE = app


SOURCES += main.cpp\
        loginform.cpp \
    charselect.cpp \
    gamewindow.cpp

HEADERS  += loginform.h \
    charselect.h \
    gamewindow.h

FORMS    += loginform.ui \
    charselect.ui \
    gamewindow.ui
