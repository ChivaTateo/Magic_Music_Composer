#ifndef TRACKVIEWER_H
#define TRACKVIEWER_H

#include <QWidget>
#include <QLayout>
#include <QCommandLinkButton>

#include "track.h"

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
public slots:
    void addTrack();
    void deleteTrack(int index);
};

#endif // TRACKVIEWER_H
