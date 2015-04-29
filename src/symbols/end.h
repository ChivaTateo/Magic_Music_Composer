#ifndef END_H
#define END_H

#include "musicsymbol.h"
#define END_SCALE 0.5

class End : public MusicSymbol
{
public:
    explicit End(QGraphicsItem *parent = 0);
    explicit End(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    void drawSymbol(qreal &lastX);
};

#endif // END_H
