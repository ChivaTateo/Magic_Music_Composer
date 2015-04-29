#ifndef KEY_H
#define KEY_H

#include "musicsymbol.h"
#define KEY_SCALE 0.9

class Key : public MusicSymbol
{
public:
    explicit Key(QGraphicsItem *parent = 0);
    explicit Key(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    void drawSymbol(qreal &lastX);
};

#endif // END_H
