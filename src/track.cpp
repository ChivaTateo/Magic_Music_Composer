#include "track.h"

Track::Track(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setScene(new QGraphicsScene());
    count = 0;
    lastX = 0;
    right = -650;

    params.push_back(2);
    params.push_back(4);

    pen.setColor(Qt::black);
    pen.setWidth(3);

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
    map.load(QCoreApplication::applicationDirPath() + "/images/note5.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/note6.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/note7.png");
    pixVect.append(map);

    drawLines(50);
    drawStart();
}

void Track::drawLines(qreal x)
{
    this->scene()->addLine(right,0,x,0,pen);
    this->scene()->addLine(right,15,x,15,pen);
    this->scene()->addLine(right,30,x,30,pen);
    this->scene()->addLine(right,45,x,45,pen);
    this->scene()->addLine(right,-15,x,-15,pen);
    right = x;
}

void Track::drawStart()
{
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(pixVect[0]);
    item->setTransformationMode(Qt::SmoothTransformation);
    item->setPos(-640,-45);
    item->setScale(0.9);
    this->scene()->addItem(item);
    lastX = item->pos().x() + item->boundingRect().width()*0.9;
    QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(params[0]));
    text->setPos(lastX + 5, -45);;
    text->setScale(4);
    this->scene()->addItem(text);

    text = new QGraphicsTextItem(QString::number(params[1]));
    text->setPos(lastX + 5, -15);
    text->setScale(4);
    this->scene()->addItem(text);
    lastX += text->boundingRect().width()*4;
}

void Track::createNote(const QString& str)
{
    int id = str.toInt();
    NoteGroup* group = new NoteGroup();
    MusicSymbol* symbol = new MusicSymbol(pixVect[1 + id], group);
    int k = qrand() % 16 - 4;
    symbol->addParam(k);
    symbol->addParam(id);

    symbol->setPos(lastX + 10,15 - k*7.6);
    symbol->setTransformationMode(Qt::SmoothTransformation);
    symbol->setScale(0.5);
    symbol->setFlag(QGraphicsItem::ItemIsSelectable);
    this->scene()->addItem(group);

    if (k < 2)
    {
        for (int i = 0; 15*i < 15 - k*7.6 + symbol->boundingRect().height()*0.5; ++i)
        {
            this->scene()->addLine(lastX+5,15*i,lastX+25,15*i, pen);
        }
    }

    if (k > 8)
    {
        for (int i = 0; -15*i > 15 - k*7.6; ++i)
        {
            this->scene()->addLine(lastX+5,-15*i,lastX+25,-15*i, pen);
        }
    }
    if(id == 0)
    {
        count = 1.0;
    }
    else
        count += 1/qPow(2,id);

    if (count >= 1.0f)
    {
        lastX += symbol->boundingRect().width()*0.5 + 10;
        count = 0;
        this->scene()->addLine(lastX+20,-15,lastX+20,45,pen);
    }

    lastX += symbol->boundingRect().width()*0.5 + 10;
    this->centerOn(lastX, 0);
    if (lastX >= right)
    {
        drawLines(right + 500);
    }
}
Track::~Track()
{
    pixVect.clear();
}
