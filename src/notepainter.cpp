#include "notepainter.h"

NotePainter::NotePainter(QWidget *parent) :
    QGraphicsView(parent)
{
    QPen pen(Qt::black);
    pen.setWidth(1);
    this->setScene(new QGraphicsScene());
    this->scene()->addLine(-500,1,50,1,pen);
    this->scene()->addLine(-500,10,50,10,pen);
    this->scene()->addLine(-500,20,50,20,pen);
    this->scene()->addLine(-500,30,50,30,pen);
    this->scene()->addLine(-500,40,50,40,pen);
    QPixmap map(QCoreApplication::applicationDirPath() + "/images/9.jpg");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(map);
    item->setPos(-500,1);
    item->setScale(0.15);
    this->scene()->addItem(item);
}
