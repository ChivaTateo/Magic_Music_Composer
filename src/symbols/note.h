#ifndef NOTE_H
#define NOTE_H

#include "musicsymbol.h"

class Note : public MusicSymbol
{
public:
    explicit Note(QGraphicsItem *parent = 0);
    explicit Note(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    void drawSymbol(qreal &lastX, QPen pen);
    void addSpec(int id);
    void clear();

    //Обработка движения мыши с зажатой кнопкой
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //Обработка отпускания мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QGraphicsPixmapItem* spec;
};

#endif // NOTE_H
