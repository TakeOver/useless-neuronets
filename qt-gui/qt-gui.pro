#-------------------------------------------------
#
# Project created by QtCreator 2013-08-23T17:28:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NN
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        LodePNG/lodepng.cpp

HEADERS  += mainwindow.h \
    paths.h \
    LodePNG/lodepng.h\
    Kohonen/Utils.hpp

FORMS    += mainwindow.ui
QMAKE_CXXFLAGS += -std=c++11

