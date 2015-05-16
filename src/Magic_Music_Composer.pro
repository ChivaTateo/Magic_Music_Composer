#-------------------------------------------------
#
# Project created by QtCreator 2015-03-15T17:54:35
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

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
    symbols/end.cpp \
    symbols/taktline.cpp \
    symbols/additline.cpp

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
    symbols/taktline.h \
    symbols/key.h \
    symbols/end.h \
    symbols/additline.h

FORMS    += \
    ui/magiccomposer.ui \
    ui/note_options.ui \
    ui/pause_options.ui \
    ui/track_options.ui \
    ui/magiccomposer_andr.ui

RESOURCES += \
    symbols.qrc \
    icons.qrc

QMAKE_CXXFLAGS += \
    -std=c++0x

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
