#include "track.h"

Track::Track(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setScene(new QGraphicsScene());
    startX = 0;

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

    drawLines();
    drawStart();

    setMouseTracking(true);
}

void Track::drawLines()
{
    this->scene()->addLine(-650,0,50,0,pen);
    this->scene()->addLine(-650,15,50,15,pen);
    this->scene()->addLine(-650,30,50,30,pen);
    this->scene()->addLine(-650,45,50,45,pen);
    this->scene()->addLine(-650,-15,50,-15,pen);
    right = 50;
}

void Track::changeLines(qreal x)
{
    QList<QGraphicsItem*> items = this->scene()->items(Qt::SortOrder::AscendingOrder);
    int count = 5;
    for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end() && count != 0; ++iter)
    {
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(*iter);
        if (line != NULL)
        {
            line->setLine(-650,(count-2)*15,x,(count-2)*15);
            --count;
        }
    }
    right = x;
}

bool less(NoteGroup* a, NoteGroup* b)
{
    return (a->childItems().first()->x() < b->childItems().first()->x());
}

QList<NoteGroup*> Track::sortListGroups()
{
    QList<QGraphicsItem*> items = this->scene()->items();
    QList<NoteGroup*> groups;

    for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
    {
        NoteGroup* group = dynamic_cast<NoteGroup*>(*iter);
        if (group != nullptr)
        {
            groups << group;
        }
    }

    qSort(groups.begin(),groups.end(),less);
    return groups;
}

void Track::update()
{
    QList<QGraphicsItem*> items = this->scene()->items();
    qreal lastX = startX;
    qreal count = 0;

    for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
    {
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(*iter);
        if (line != NULL)
        {
            this->scene()->removeItem(line);
        }
    }

    QList<NoteGroup*> groups = sortListGroups();
    drawLines();

    for (QList<NoteGroup*>::iterator iter = groups.begin(); iter != groups.end(); ++iter)
    {
        NoteGroup* group = *iter;
        if (group != NULL)
        {
            QList<QGraphicsItem*> notes = group->childItems();
            bool first = true;
            for (QList<QGraphicsItem*>::iterator iter_n = notes.begin(); iter_n != notes.end(); ++iter_n)
            {
                MusicSymbol* symbol = dynamic_cast<MusicSymbol*>(*iter_n);
                QVector<int> params = symbol->getParams();
                if (params[0] != 100)
                {
                    if(params[1] == 0)
                        symbol->setPos(lastX + 20 - symbol->boundingRect().width()*0.25,
                                   params[0]*7.5 - symbol->boundingRect().height()*0.25);
                    else
                        symbol->setPos(lastX + 20 - symbol->boundingRect().width()*0.25,
                                   params[0]*7.5 - symbol->boundingRect().height()*0.43);

                    if (params[0] < -3)
                    {
                        for (int i = 1; (i+1)*-15 > symbol->pos().y() + symbol->boundingRect().height()*0.25; ++i)
                        {
                            this->scene()->addLine(lastX+10,(i+1)*-15,lastX+25,(i+1)*-15, pen);
                        }
                    }

                 /*   if (params[0] > 8)
                    {
                        for (int i = 0; -15*i > 15 - k*7.6; ++i)
                        {
                            this->scene()->addLine(lastX+5,-15*i,lastX+25,-15*i, pen);
                        }
                    }
                    */

                    if (first)
                    {
                        if(params[1] == 0)
                        {
                            count = 1.0;
                        }
                        else
                            count += 1/qPow(2,params[1]);

                        first = false;
                    }

                }
            }

            if (count >= 1.0f)
            {
                lastX += notes.first()->boundingRect().width()*0.5 + 10;
                count = 0;
                this->scene()->addLine(lastX+20,-15,lastX+20,45,pen);
            }

            lastX += notes.first()->boundingRect().width()*0.5 + 10;
            if (lastX >= right)
            {
                changeLines(right + 500);
            }

        }
    }
}

void Track::drawStart()
{
    MusicSymbol* item = new MusicSymbol(pixVect[0]);
    item->setTransformationMode(Qt::SmoothTransformation);
    item->setPos(-640,-45);
    item->setScale(0.9);
    item->addParam(100);
    this->scene()->addItem(item);
    int lastX = item->pos().x() + item->boundingRect().width()*0.9;

    QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(params[0]));
    text->setPos(lastX + 5, -45);;
    text->setScale(4);
    this->scene()->addItem(text);

    text = new QGraphicsTextItem(QString::number(params[1]));
    text->setPos(lastX + 5, -15);
    text->setScale(4);
    this->scene()->addItem(text);
    lastX += text->boundingRect().width()*4;
    startX = lastX;
}

void Track::createNote(const QString& str)
{
    int id = str.toInt();
    NoteGroup* group = new NoteGroup;
    MusicSymbol* symbol = new MusicSymbol(pixVect[id+1], group);
    int k = qrand()%16-4;
    symbol->addParam(k);
    symbol->addParam(id);

    symbol->setTransformationMode(Qt::SmoothTransformation);
    symbol->setScale(0.5);
    symbol->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    symbol->setFlag(QGraphicsItem::ItemIsMovable);
    symbol->setFlag(QGraphicsItem::ItemIsSelectable);
    this->scene()->addItem(group);

    update();
}

Track::~Track()
{
    pixVect.clear();
}
