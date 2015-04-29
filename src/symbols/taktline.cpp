#include "taktline.h"
#include "../widgets/track.h"

TaktLine::TaktLine(QGraphicsItem *parent):
    MusicSymbol(parent)
{
}

TaktLine::TaktLine(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    MusicSymbol(track,pixmap,parent)
{
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setScale(TAKT_SCALE);
}

void TaktLine::drawSymbol(qreal &lastX)
{
    this->setPos(lastX-20,-SIZE_BETWEEN_LINES);
    lastX += this->boundingRect().width()*TAKT_SCALE - 20;
}

void TaktLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF mousePos = event->scenePos();

    track->setSelectRect(mousePos.x()-this->boundingRect().width()*NOTE_SCALE_FOR_CENTER,
                         -60, 20, 130);

}

void TaktLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (track->getSelectRect()->rect().width() != 0)
    {
        QPointF newPos = event->scenePos();
        this->setPos(newPos);

        track->setSelectRect(0,0,0,0);
        track->update();
    }
}
