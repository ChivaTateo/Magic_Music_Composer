#include "musicsymbol.h"
#include "../widgets/track.h"

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
        if (!Track::ctrl)
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

void MusicSymbol::deleteSymbol()
{
    if (this->parentItem()->childItems().size() == 1)
        this->scene()->removeItem(this->parentItem());
    else
    {
        this->setParentItem(nullptr);
        track->scene()->removeItem(this);
    }
}

MusicSymbol::~MusicSymbol()
{
    params.clear();
}

