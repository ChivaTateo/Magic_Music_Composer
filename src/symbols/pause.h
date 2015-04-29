#ifndef PAUSE_H
#define PAUSE_H

#include "musicsymbol.h"
#define PAUSE_SCALE 0.6

class Pause : public MusicSymbol
{
public:
    explicit Pause(QGraphicsItem *parent = 0);
    explicit Pause(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    void drawSymbol(qreal &lastX);

    //Обработка движения мыши с зажатой кнопкой
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //Обработка отпускания мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PAUSE_H
