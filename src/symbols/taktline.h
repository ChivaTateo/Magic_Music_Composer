#ifndef TAKTLINES_H
#define TAKTLINES_H

#include <QGraphicsLineItem>

class TaktLine : public QGraphicsLineItem
{
public:
    explicit TaktLine(QGraphicsItem *parent = 0):
        QGraphicsLineItem(parent)
    {
    }

    explicit TaktLine(qreal x1,qreal y1,qreal x2,qreal y2,QPen pen,QGraphicsItem *parent = 0):
        QGraphicsLineItem(x1,y1,x2,y2,parent)
    {
        this->setPen(pen);
    }

};

#endif // TAKTLINES_H
