#ifndef TRACKVIEWER_H
#define TRACKVIEWER_H

#include <QWidget>
#include <QLayout>
#include <QCommandLinkButton>
#include "track.h"

#ifdef Q_OS_ANDROID
    #define MAX_TRACKS 2
#else
    #define MAX_TRACKS 4
#endif

class TrackViewer : public QWidget
{
    Q_OBJECT
    QList<Track*> tracks;
    QList<QPushButton*> buttons;

    QCommandLinkButton* button;
    QGridLayout* layout;
    QSignalMapper* mapper;

public:
    explicit TrackViewer(QWidget *parent = 0);
    QList<Track*> getTracks();
    void scaleTrack(bool scaled);
    ~TrackViewer();
public slots:
    void addTrack();
    void deleteTrack(int index);
    void focusChange();

    void createNote(int id);
    void createPause(int id);
    void createTakt(int id);
};

#endif // TRACKVIEWER_H
