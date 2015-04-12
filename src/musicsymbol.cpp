#include "musicsymbol.h"
#include "track.h"

bool MusicSymbol::ctrl = false;

MusicSymbol::MusicSymbol(QGraphicsItem *parent):
       QGraphicsPixmapItem(parent)
{
    setAcceptTouchEvents(true);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
    track = nullptr;
}

MusicSymbol::MusicSymbol(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    QGraphicsPixmapItem(pixmap, parent)
{
    this->track = track;
    setAcceptTouchEvents(true);
    setAcceptHoverEvents(true);
    setAcceptDrops(true);
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

void MusicSymbol::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!ctrl)
        {
             Track* track = dynamic_cast<Track*>(this->scene()->views().at(0));
             QList<QGraphicsItem*> items = track->scene()->selectedItems();

             for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
             {
                 (*iter)->setSelected(false);
             }
        }
        this->setSelected(!this->isSelected());
    }
}

void MusicSymbol::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();
//    if (this->parentItem()->childItems().size() == 1)
//    {
//        if (mousePos.x() > pos().x())
//            this->setX(mousePos.x() - this->boundingRect().width()*0.5 - 5);
//        else
//            this->setX(mousePos.x() + 5);
//    }
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

void MusicSymbol::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Track* track = dynamic_cast<Track*>(this->scene()->views().at(0));
    if (track->getSelectRect()->rect().width() != 0)
    {
        QPointF newPos = event->scenePos();
        QList<QGraphicsItem*> items = track->getSelectRect()->collidingItems();
        bool haveSymbols = false;

        for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
        {
            MusicSymbol* symbol = dynamic_cast<MusicSymbol*>(*iter);
            if (symbol != nullptr)
            {
                haveSymbols = true;
                NoteGroup* group = dynamic_cast<NoteGroup*>(symbol->parentItem());
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

void MusicSymbol::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        ctrl = true;
    else if (event->key() == Qt::Key_Delete)
    {
        if (this->isSelected())
        {
            if (this->parentItem()->childItems().size() == 1)
                this->scene()->removeItem(this->parentItem());
            else
            {
                this->setParentItem(nullptr);
                track->scene()->removeItem(this);
            }
        }
        track->update();
    }


}

void MusicSymbol::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        ctrl = false;
}

MusicSymbol::~MusicSymbol()
{
    params.clear();
}

