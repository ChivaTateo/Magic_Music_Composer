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
    track.cpp \
    musicsymbol.cpp \
    trackviewer.cpp \
    projectviewer.cpp \
    magiccomposer.cpp \
    options.cpp

HEADERS  += \
    musicsymbol.h \
    notegroup.h \
    track.h \
    trackviewer.h \
    projectviewer.h \
    magiccomposer.h \
    options.h

FORMS    += \
    magiccomposer.ui \
    options_1.ui \
    options_2.ui
