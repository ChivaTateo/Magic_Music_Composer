#include "musicsymbol.h"
#include "track.h"

MusicSymbol::MusicSymbol(QGraphicsItem *parent):
       QGraphicsPixmapItem(parent)
{
    setAcceptTouchEvents(true);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    click = false;
}

MusicSymbol::MusicSymbol(const QPixmap &pixmap, QGraphicsItem *parent):
    QGraphicsPixmapItem(pixmap, parent)
{
    setAcceptTouchEvents(true);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    click = false;
}

QVector<int> MusicSymbol::getParams()
{
    return params;
}

void MusicSymbol::addParam(int param)
{
    params.push_back(param);
}

void MusicSymbol::changeParam(int param, int i)
{
    params[i] = param;
}

void MusicSymbol::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF newPos = event->scenePos();
    Track* track = dynamic_cast<Track*>(this->scene()->views().at(0));
    QList<NoteGroup*> groups = track->sortListGroups();
    NoteGroup* oldGroup = nullptr;

    setFlag(QGraphicsItem::ItemSendsScenePositionChanges,false);
    for (QList<NoteGroup*>::iterator iter = groups.begin(); iter != groups.end(); ++iter)
    {
        NoteGroup* group = *iter;
        if (group != nullptr)
        {
            if (group->isChild(this))
            {
                if (newPos.x() + 20 < pos().x())
                {
                    if (group->childItems().size() == 1)
                    {
                        if (oldGroup != nullptr)
                        {
                            this->scene()->removeItem(group);
                            this->setParentItem(oldGroup);
                        }
                    }
                    else
                    {
                        NoteGroup* newGroup = new NoteGroup;
                        this->setParentItem(newGroup);
                        track->scene()->addItem(newGroup);
                    }
                    break;
                }

                if (newPos.x() - 20 > pos().x())
                {
                    if (group->childItems().size() == 1)
                    {
                        QList<NoteGroup*>::iterator now = iter++;
                        if (iter != groups.end())
                        {
                            this->scene()->removeItem(*now);
                            this->setParentItem(*iter);
                        }
                    }
                    else
                    {
                        NoteGroup* newGroup = new NoteGroup;
                        this->setParentItem(newGroup);
                        track->scene()->addItem(newGroup);
                    }
                    break;
                }
            }
            oldGroup = group;
        }
    }

    newPos.setY(newPos.y() - this->boundingRect().height()*0.43);
    for(int i = -6; i < 12; ++i)
    {
        if (params[1] == 0)
        {
            if (newPos.y() >=  (i-1)*7.5 - this->boundingRect().height()*0.25 &&
                newPos.y() <=  (i)*7.5 - this->boundingRect().height()*0.25)
            {
                changeParam(i, 0);
                break;
            }
        }
        else
        {
            if (newPos.y() >=  (i-1)*7.5 - this->boundingRect().height()*0.43 &&
                newPos.y() <=  (i)*7.5 - this->boundingRect().height()*0.43)
            {
                changeParam(i, 0);
                break;
            }
        }
    }
    this->setPos(newPos);
    track->update();
}


MusicSymbol::~MusicSymbol()
{
    params.clear();
}

