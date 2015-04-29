#include "end.h"

End::End(QGraphicsItem *parent):
    MusicSymbol(parent)
{
}

End::End(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    MusicSymbol(track, pixmap, parent)
{
}

void End::drawSymbol(qreal &lastX)
{
    this->setPos(lastX - this->boundingRect().width()*END_SCALE + 2,-SIZE_BETWEEN_LINES);
}
