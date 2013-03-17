#-------------------------------------------------
#
# Project created by QtCreator 2013-03-17T22:38:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = face
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        livevideo.cpp

HEADERS  += mainwindow.h\
            livevideo.h

FORMS    += mainwindow.ui

unix: LIBS += -L$$PWD/../../../../usr/local/lib/ -lopencv_calib3d -lopencv_imgproc -lopencv_video -lopencv_objdetect -lopencv_core -lopencv_highgui

INCLUDEPATH += $$PWD/../../../../usr/local/lib
DEPENDPATH += $$PWD/../../../../usr/local/lib
