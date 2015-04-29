#ifndef TAKTLINES_H
#define TAKTLINES_H

#include "musicsymbol.h"
#define TAKT_SCALE 0.5

class Track;

class TaktLine : public MusicSymbol
{
public:
    explicit TaktLine(QGraphicsItem *parent = 0);
    explicit TaktLine(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    void drawSymbol(qreal &lastX);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // TAKTLINES_H
