#ifndef TRACKVIEWER_H
#define TRACKVIEWER_H

#include <QWidget>
#include <QLayout>
#include <QCommandLinkButton>
#include <QPropertyAnimation>
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
    void scaleTrack(bool scaled);
    ~TrackViewer();
public slots:
    void addTrack();
    void deleteTrack(int index);
    void focusChange();
};

#endif // TRACKVIEWER_H
