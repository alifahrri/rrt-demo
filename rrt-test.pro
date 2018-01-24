#-------------------------------------------------
#
# Project created by QtCreator 2017-10-08T15:53:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rrt-test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += include

SOURCES += main.cpp \
    gui/graphicsview.cpp \
    gui/mainwindow.cpp \
    gui/polygonitem.cpp \
    gui/rrtitem.cpp \
    src/kdtree.cpp \
    src/line.cpp \
    src/polygon.cpp \
    src/rrt.cpp



FORMS    += gui/mainwindow.ui

HEADERS += \
    3rdparty/nanoflann.hpp \
    gui/graphicsview.h \
    gui/mainwindow.h \
    gui/polygonitem.h \
    gui/rrtitem.h \
    include/kdtree.h \
    include/line.h \
    include/pointcloud.h \
    include/polygon.h \
    include/rrt.h
