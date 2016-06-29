#-------------------------------------------------
#
# Project created by QtCreator 2016-06-28T22:54:05
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SRSaveEditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xmlsaveparser.cpp \
    item.cpp \
    sets.cpp

HEADERS  += mainwindow.h \
    xmlsaveparser.h \
    item.h \
    sets.h

FORMS    += mainwindow.ui
