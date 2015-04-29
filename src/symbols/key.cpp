#include "key.h"

Key::Key(QGraphicsItem *parent):
    MusicSymbol(parent)
{
}

Key::Key(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    MusicSymbol(track, pixmap, parent)
{
}

void Key::drawSymbol(qreal &lastX)
{
    if (this->getParams()[0] == 1)
        this->setPos(-650,-1.5*SIZE_BETWEEN_LINES);
    else
        this->setPos(-650,-3*SIZE_BETWEEN_LINES);

    lastX = this->pos().x() + this->boundingRect().width()*KEY_SCALE;
}
