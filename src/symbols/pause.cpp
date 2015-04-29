#include "pause.h"
#include "../widgets/track.h"

Pause::Pause(QGraphicsItem *parent):
    MusicSymbol(parent)
{
    this->addParam(2);
    this->setTransformationMode(Qt::SmoothTransformation);
    this->setScale(PAUSE_SCALE);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

Pause::Pause(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    MusicSymbol(track, pixmap, parent)
{
    this->setTransformationMode(Qt::SmoothTransformation);
    this->setScale(PAUSE_SCALE);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

void Pause::drawSymbol(qreal &lastX)
{
    this->setPixmap(QPixmap(":/pauses/"+QString::number(params[0])));

    this->setPos(lastX - this->boundingRect().width()*PAUSE_SCALE,
                 3*SIZE_BETWEEN_LINES - this->boundingRect().height()*PAUSE_SCALE);
}

void Pause::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();

    track->setSelectRect(mousePos.x()-this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,
                         -60, 20, 130);
}

void Pause::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (track->getSelectRect()->rect().width() != 0)
    {
        QPointF newPos = event->scenePos();
        this->setPos(newPos);

        track->setSelectRect(0,0,0,0);
        track->update();
    }
}
