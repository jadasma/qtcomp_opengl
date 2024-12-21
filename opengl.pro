#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T20:43:46
#
#-------------------------------------------------

QT += core gui widgets opengl openglwidgets


CONFIG += c++17


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    miwidget.cpp

HEADERS += mainwindow.h \
    miwidget.h

FORMS += mainwindow.ui
LIBS += -lOpengl32
DISTFILES +=

