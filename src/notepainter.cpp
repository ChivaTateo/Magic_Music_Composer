#include "notepainter.h"

NotePainter::NotePainter(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setScene(new QGraphicsScene());
    track = new Track;
    track->initTest();

    QPixmap map(QCoreApplication::applicationDirPath() + "/images/key1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/note0.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/note1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/note2.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/note3.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/note4.png");
    pixVect.append(map);

}

void NotePainter::update()
{
    QPen pen(Qt::black);
    pen.setWidth(3);
    this->scene()->clear();

    drawLines(pen);
    drawStart();
    drawNotes(pen);
}

void NotePainter::drawLines(QPen pen)
{
    this->scene()->addLine(-640,0,50,0,pen);
    this->scene()->addLine(-640,15,50,15,pen);
    this->scene()->addLine(-640,30,50,30,pen);
    this->scene()->addLine(-640,45,50,45,pen);
    this->scene()->addLine(-640,-15,50,-15,pen);
}

void NotePainter::drawStart()
{
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixVect[0]);
    item->setTransformationMode(Qt::SmoothTransformation);
    item->setPos(-640,-45);
    item->setScale(0.9);
    this->scene()->addItem(item);
    lastX = item->pos().x() + item->boundingRect().width()*0.9;
    QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(this->track->getParams()[0]));
    text->setPos(lastX + 5, -45);;
    text->setScale(4);
    this->scene()->addItem(text);

    text = new QGraphicsTextItem(QString::number(this->track->getParams()[1]));
    text->setPos(lastX + 5, -15);
    text->setScale(4);
    this->scene()->addItem(text);
    lastX += text->boundingRect().width()*4;
}

void NotePainter::drawNotes(QPen pen)
{
    qDebug() << "notes";
    float count = 0;

    QList<QList<MusicSymbol*>>::const_iterator bigIter;
    QList<MusicSymbol*>::const_iterator smallIter;
    for(bigIter = track->getNotes().constBegin(); bigIter != track->getNotes().constEnd(); ++bigIter)
    {
        qDebug() << "start";
        QGraphicsPixmapItem* item;
        for(smallIter = (*bigIter).constBegin(); smallIter != (*bigIter).constEnd(); ++smallIter)
        {
            qDebug() << "smallIter";
            item = new QGraphicsPixmapItem(pixVect[1 + (*smallIter)->getParams()[1]]);
            item->setPos(lastX + 10,15 - (*smallIter)->getParams()[0]*7.6);
            item->setTransformationMode(Qt::SmoothTransformation);
            item->setScale(0.5);
            this->scene()->addItem(item);
        }


        if((*bigIter).first()->getParams()[1] == 0)
        {
            count = 1.0;
        }
        else
            count += 1/qPow(2,(*bigIter).first()->getParams()[1]);

        qDebug() << count;
        if (count >= 1.0f)
        {
            lastX += item->boundingRect().width()*0.5 + 10;
            count = 0;
            this->scene()->addLine(lastX+20,-15,lastX+20,45,pen);
        }

        lastX += item->boundingRect().width()*0.5 + 10;
    }
    qDebug() << "endNotes";
}

NotePainter::~NotePainter()
{
    delete track;
    pixVect.clear();
}
