#ifndef TRACKVIEWER_H
#define TRACKVIEWER_H

#include <QWidget>
#include <QLayout>
#include "track.h"

class TrackViewer : public QScrollArea
{
    Q_OBJECT
    QList<Track*> tracks;
public:
    explicit TrackViewer(QWidget *parent = 0);
    void addTrack();
    QList<Track*> getTracks();    
};

#endif // TRACKVIEWER_H
