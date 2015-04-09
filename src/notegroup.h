#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QtCore>
#include "musicsymbol.h"

class NoteGroup : public QGraphicsPathItem
{
private:
    int id;
public:
    explicit NoteGroup(QGraphicsItem *parent = 0):
        QGraphicsPathItem(parent)
    {
    }

    ~NoteGroup()
    {
    }

};

#endif // TRACK_H
