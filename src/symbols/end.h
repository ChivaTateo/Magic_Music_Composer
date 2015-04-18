#ifndef END_H
#define END_H

#include "musicsymbol.h"

class End : public MusicSymbol
{
public:
    explicit End(QGraphicsItem *parent = 0);
    explicit End(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    void drawSymbol(qreal &lastX, QPen pen);
};

#endif // END_H
