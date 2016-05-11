#-------------------------------------------------
#
# Project created by QtCreator 2016-05-09T10:41:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = graphicsItemWithFiles
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    background.cpp \
    boxitem.cpp \
    fileitem.cpp

HEADERS  += widget.h \
    background.h \
    boxitem.h \
    fileitem.h

FORMS    += widget.ui
