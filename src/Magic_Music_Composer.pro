#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T17:54:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Magic_Music_Composer
TEMPLATE = app


SOURCES += main.cpp\
    test.cpp \
    track.cpp \
    musicsymbol.cpp \
    trackviewer.cpp \
    projectviewer.cpp \
    magiccomposer.cpp

HEADERS  += \
    musicsymbol.h \
    test.h \
    notegroup.h \
    track.h \
    trackviewer.h \
    projectviewer.h \
    magiccomposer.h

FORMS    += \
    test.ui \
    magiccomposer.ui
