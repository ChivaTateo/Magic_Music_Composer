#include "trackviewer.h"

TrackViewer::TrackViewer(QWidget *parent) :
    QScrollArea(parent)
{
}

void TrackViewer::addTrack()
{
    if (tracks.size() < 4)
    {
        Track* track = new Track(this);
        this->layout()->addWidget(track);
        track->show();
        track->setFocus();
        tracks.append(track);
    }
}
