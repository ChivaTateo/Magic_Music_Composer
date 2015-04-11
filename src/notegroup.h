#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QtCore>
#include "musicsymbol.h"

class NoteGroup : public QGraphicsItem
{
public:
    NoteGroup() {}

    ~NoteGroup()
    {
    }

    QRectF boundingRect() const
    {
        return QRectF(0,0,0,0);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {

    }

    bool isChild(QGraphicsItem* item)
    {
        bool res = false;

        QList<QGraphicsItem*> childs = childItems();

        for (QList<QGraphicsItem*>::iterator iter = childs.begin(); iter != childs.end(); ++iter)
        {
             if (*iter == item)
             {
                 res = true;
                 break;
             }
        }

        return res;
    }
};

#endif // TRACK_H
