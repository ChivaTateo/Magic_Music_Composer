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
    symbols/musicsymbol.cpp \
    widgets/magiccomposer.cpp \
    widgets/options.cpp \
    widgets/projectviewer.cpp \
    widgets/track.cpp \
    widgets/trackviewer.cpp \
    symbols/note.cpp \
    symbols/pause.cpp \
    symbols/key.cpp \
    symbols/end.cpp

HEADERS  += \
    symbols/musicsymbol.h \
    symbols/notegroup.h \
    widgets/magiccomposer.h \
    widgets/options.h \
    widgets/projectviewer.h \
    widgets/track.h \
    widgets/trackviewer.h \
    symbols/note.h \
    symbols/pause.h \
    symbols/key.h \
    symbols/end.h

FORMS    += \
    ui/magiccomposer.ui \
    ui/note_options.ui \
    ui/pause_options.ui \
    ui/track_options.ui
