#ifndef ADDITLINE_H
#define ADDITLINE_H

#include <QGraphicsLineItem>
#include <QPen>

class AdditLine : public QGraphicsLineItem
{
public:
    explicit AdditLine(QGraphicsItem *parent = 0);
    explicit AdditLine(qreal x1,qreal y1, qreal x2, qreal y2, QPen pen, QGraphicsItem* parent = 0);
};

#endif // ADDITLINES_H
