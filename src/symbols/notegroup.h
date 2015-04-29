#ifndef NOTEGROUP_H
#define NOTEGROUP_H

#include <QGraphicsItem>
#include "note.h"
#include "pause.h"
#include "key.h"
#include "end.h"

class NoteGroup : public QGraphicsRectItem
{
public:
    NoteGroup() {}

    ~NoteGroup()
    {
    }

    //Является ли item ребенком данного объекта
    bool hasChild(QGraphicsItem* item)
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
