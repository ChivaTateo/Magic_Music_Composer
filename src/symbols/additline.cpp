#include "additline.h"

AdditLine::AdditLine(QGraphicsItem *parent) :
    QGraphicsLineItem(parent)
{
}

AdditLine::AdditLine(qreal x1, qreal y1, qreal x2, qreal y2, QPen pen, QGraphicsItem *parent):
    QGraphicsLineItem(x1,y1,x2,y2,parent)
{
    this->setPen(pen);
}
