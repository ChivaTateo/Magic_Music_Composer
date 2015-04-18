#include "key.h"

Key::Key(QGraphicsItem *parent):
    MusicSymbol(parent)
{
}

Key::Key(Track* track, const QPixmap &pixmap, QGraphicsItem *parent):
    MusicSymbol(track, pixmap, parent)
{
}

void Key::drawSymbol(qreal &lastX, QPen pen)
{

}
