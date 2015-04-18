#include "end.h"

End::End(QGraphicsItem *parent):
    MusicSymbol(parent)
{
}

End::End(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    MusicSymbol(track, pixmap, parent)
{
}

void End::drawSymbol(qreal &lastX, QPen pen)
{

}
