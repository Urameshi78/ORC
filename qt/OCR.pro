#-------------------------------------------------
#
# Project created by QtCreator 2015-11-09T15:59:32
#
#-------------------------------------------------

QT       += core
QT       += widgets
QT       -= gui

TARGET = OCR
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += .
INCLUDEPATH += .usr/include
INCLUDEPATH += .usr/include/opencv
INCLUDEPATH += .usr/include/opencv2
INCLUDEPATH += .usr/include/opencv2/core
INCLUDEPATH += .usr/include/opencv2/highgui
INCLUDEPATH += .usr/include/opencv2/imgproc
INCLUDEPATH += .usr/include/opencv2/flann
INCLUDEPATH += .usr/include/opencv2/photo
INCLUDEPATH += .usr/include/opencv2/video
INCLUDEPATH += .usr/include/opencv2/features2d
INCLUDEPATH += .usr/include/opencv2/objdetect
INCLUDEPATH += .usr/include/opencv2/calib3d
INCLUDEPATH += .usr/include/opencv2/ml
INCLUDEPATH += .usr/include/opencv2/contrib
LIBS += `pkg-config opencv --cflags --libs`

SOURCES += main.cpp \
        window.cpp \
    learnwindow.cpp \
    imagewindow.cpp \
    loadwindow.cpp \
    quitwindow.cpp

HEADERS += \
        window.h \
    learnwindow.h \
    imagewindow.h \
    loadwindow.h \
    loadwindow.h \
    quitwindow.h
