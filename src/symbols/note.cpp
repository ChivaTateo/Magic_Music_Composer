#include "note.h"
#include "../widgets/track.h"

Note::Note(QGraphicsItem *parent):
    MusicSymbol(parent)
{
    spec = nullptr;
    this->addParam(0);
    this->addParam(0);
    this->setTransformationMode(Qt::SmoothTransformation);
    this->setScale(NOTE_SCALE);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

Note::Note(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    MusicSymbol(track, pixmap, parent)
{
    spec = nullptr;
    this->addParam(0);
    this->setTransformationMode(Qt::SmoothTransformation);
    this->setScale(NOTE_SCALE);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

void Note::drawSymbol(qreal &lastX, QPen pen)
{
    this->setPixmap(QPixmap(":/notes/"+QString::number(params[1])));
    if(params[1] == 0)
    {
        if(params.size() > 2)
        {
            spec->setPixmap(QPixmap(":/special/"+QString::number(params[2])));
            spec->setPos(-spec->boundingRect().width()*SPEC_SCALE,
                         -this->boundingRect().height()*NOTE_SCALE);
        }

        this->setPos(lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,
                     params[0]*HALF_SIZE - this->boundingRect().height()*NOTE_SCALE_FOR_CENTER);

        if (params[0] < -3)
        {
            for (int i = 1; (i+1)*-SIZE_BETWEEN_LINES >= this->pos().y() + this->boundingRect().height()*NOTE_SCALE_FOR_CENTER; ++i)
            {
                this->scene()->addItem(new TaktLine(lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,(i+1)*-SIZE_BETWEEN_LINES,
                                       lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER+20,(i+1)*-SIZE_BETWEEN_LINES, pen));
            }
        }

        if (params[0] > 7)
        {
            for (int i = 3; (i+1)*SIZE_BETWEEN_LINES <= this->pos().y() + this->boundingRect().height()*NOTE_SCALE_FOR_CENTER; ++i)
            {
                this->scene()->addItem(new TaktLine(lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,(i+1)*SIZE_BETWEEN_LINES,
                                       lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER+20,(i+1)*SIZE_BETWEEN_LINES, pen));
            }
        }
    }
    else
    {
        if(params.size() > 2)
        {
            spec->setPixmap(QPixmap(":/special/"+QString::number(params[2])));
            spec->setPos(-spec->boundingRect().width()*SPEC_SCALE,
                         this->boundingRect().height()*NOTE_SCALE);
        }
        this->setPos(lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,
                   params[0]*HALF_SIZE - this->boundingRect().height()*LONG_NOTE_SCALE_FOR_CENTER);

        if (params[0] < -3)
        {
            for (int i = 1; (i+1)*-SIZE_BETWEEN_LINES >= this->pos().y() + this->boundingRect().height()*NOTE_SCALE - HALF_SIZE; ++i)
            {
                this->scene()->addItem(new TaktLine(lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,(i+1)*-SIZE_BETWEEN_LINES,
                                       lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER+20,(i+1)*-SIZE_BETWEEN_LINES, pen));
            }
        }

        if (params[0] > 7)
        {
            for (int i = 3; (i+1)*SIZE_BETWEEN_LINES <= this->pos().y() + this->boundingRect().height()*NOTE_SCALE; ++i)
            {
                this->scene()->addItem(new TaktLine(lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,(i+1)*SIZE_BETWEEN_LINES,
                                       lastX - this->boundingRect().width()*NOTE_SCALE_FOR_CENTER+20,(i+1)*SIZE_BETWEEN_LINES, pen));
            }
        }
    }
}

void Note::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();

    mousePos.setY(mousePos.y() - this->boundingRect().height()*LONG_NOTE_SCALE_FOR_CENTER);

    track->setSelectRect(mousePos.x()-this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,
                         -60, 20, 130);

    for(int i = -6; i < 12; ++i)
    {
        if (params[1] == 0)
        {
            if (mousePos.y() >=  (i-1)*HALF_SIZE - this->boundingRect().height()*NOTE_SCALE_FOR_CENTER &&
                mousePos.y() <=  (i)*HALF_SIZE - this->boundingRect().height()*NOTE_SCALE_FOR_CENTER)
            {
                changeParam(i, 0);
                break;
            }
        }
        else
        {
            if (mousePos.y() >=  (i-1)*HALF_SIZE - this->boundingRect().height()*LONG_NOTE_SCALE_FOR_CENTER &&
                mousePos.y() <=  (i)*HALF_SIZE - this->boundingRect().height()*LONG_NOTE_SCALE_FOR_CENTER)
            {
                changeParam(i, 0);
                break;
            }
        }
    }
    track->update();
}

void Note::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (track->getSelectRect()->rect().width() != 0)
    {
        QPointF newPos = event->scenePos();
        QList<QGraphicsItem*> items = track->getSelectRect()->collidingItems();
        bool haveSymbols = false;

        for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
        {
            Note* note = dynamic_cast<Note*>(*iter);
            if (note != nullptr)
            {
                haveSymbols = true;
                NoteGroup* group = static_cast<NoteGroup*>(note->parentItem());
                if (group != nullptr)
                {
                    if (group->hasChild(this))
                    {
                        break;
                    }

                    if (this->parentItem()->childItems().size() == 1)
                    {
                        this->scene()->removeItem(this->parentItem());
                    }
                    this->setParentItem(group);
                    break;
                }
            }
        }

        if (!haveSymbols)
        {
            if (this->parentItem()->childItems().size() != 1)
            {
                NoteGroup* group = new NoteGroup;
                this->setParentItem(group);
                track->scene()->addItem(group);
            }
            this->setPos(newPos);
        }
        track->setSelectRect(0,0,0,0);
        track->update();
    }
}

void Note::addSpec(int id)
{
    this->addParam(id);
    spec = new QGraphicsPixmapItem(QPixmap(":/special/"+QString::number(id)),this);
    spec->setScale(SPEC_SCALE);
    spec->setTransformationMode(Qt::SmoothTransformation);
}

void Note::clear()
{
    if (spec != nullptr)
    {
        spec->setParentItem(nullptr);
        this->scene()->removeItem(spec);
        params.pop_back();
    }
    spec = nullptr;
}
