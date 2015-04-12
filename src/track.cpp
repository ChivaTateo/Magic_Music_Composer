#include "track.h"

Track::Track(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setScene(new QGraphicsScene());
    startX = 0;

    //Первоначальные параметры трека при создании
    params.push_back(2);
    params.push_back(4);

    pen.setColor(Qt::black);
    pen.setWidth(3);

    //Заполнение массива иконок
    QPixmap map(QCoreApplication::applicationDirPath() + "/images/key1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/key2.png");
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

    map.load(QCoreApplication::applicationDirPath() + "/images/pause1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/pause2.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/pause3.png");
    pixVect.append(map);

    map.load(QCoreApplication::applicationDirPath() + "/images/end1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/end2.png");
    pixVect.append(map);

    setMouseTracking(true);

    //Создание кисти для курсора и самого курсора
    QBrush newBrush(Qt::blue);

    selectRect = new QGraphicsRectItem(0,0,0,0);
    selectRect->setBrush(newBrush);
    selectRect->setOpacity(0.1);
    this->scene()->addItem(selectRect);

    key = new MusicSymbol(this, pixVect[0]);
    end = new MusicSymbol(this, pixVect[END_START]);

    //Прорисовка старта
    drawLines();
    drawStart();
}


//Первоначальная прорисовка нотоносца(линии)
void Track::drawLines()
{
    this->scene()->addLine(-650,0,50,0,pen);
    this->scene()->addLine(-650,15,50,15,pen);
    this->scene()->addLine(-650,30,50,30,pen);
    this->scene()->addLine(-650,45,50,45,pen);
    this->scene()->addLine(-650,-15,50,-15,pen);
    right = 50;
    end->setPos(right - end->boundingRect().width()*END_SCALE + 2,-15);
}

//Удлинение линий
//x - крайняя правая точка
void Track::changeLines(qreal x)
{
    QList<QGraphicsItem*> items = this->scene()->items(Qt::SortOrder::AscendingOrder);
    int count = 5;
    for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end() && count != 0; ++iter)
    {
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(*iter);
        if (line != NULL)
        {
            line->setLine(-650,(count-2)*SIZE,x,(count-2)*SIZE);
            --count;
        }
    }

    right = x;
    end->setPos(right - end->boundingRect().width()*END_SCALE + 2,-15);
}

//Функция, необходимая для сортировки списка по координате X
bool less(NoteGroup* a, NoteGroup* b)
{
    return (a->childItems().first()->x() < b->childItems().first()->x());
}

//Создание и сортировка списка групп нот по координате X
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

//Удаление всех тактовых линий
void Track::deleteTactLines()
{
    QList<QGraphicsItem*> items = this->scene()->items();

    for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
    {
        QGraphicsLineItem* line = dynamic_cast<QGraphicsLineItem*>(*iter);
        if (line != nullptr)
        {
            this->scene()->removeItem(line);
        }
    }
}

//Изменение координат в зависимости от параметров symbol
void Track::drawNote(MusicSymbol *symbol, qreal lastX)
{
    QVector<int> params = symbol->getParams();
    if (params[0] != 100)
    {
        symbol->setPixmap(pixVect[NOTE_START + params[1]]);
        if(params[1] == 0)
            symbol->setPos(lastX - symbol->boundingRect().width()*NOTE_SCALE_FOR_CENTER,
                       params[0]*HALF_SIZE - symbol->boundingRect().height()*NOTE_SCALE_FOR_CENTER);
        else
            symbol->setPos(lastX - symbol->boundingRect().width()*NOTE_SCALE_FOR_CENTER,
                       params[0]*HALF_SIZE - symbol->boundingRect().height()*LONG_NOTE_SCALE_FOR_CENTER);

        if (params[0] < -3)
        {
            for (int i = 1; (i+1)*-SIZE > symbol->pos().y() + symbol->boundingRect().height()*NOTE_SCALE_FOR_CENTER; ++i)
            {
                this->scene()->addLine(lastX - symbol->boundingRect().width()*NOTE_SCALE_FOR_CENTER,(i+1)*-SIZE,
                                       lastX - symbol->boundingRect().width()*NOTE_SCALE_FOR_CENTER+20,(i+1)*-SIZE, pen);
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
    }
}

//Обновление виджета и координат нот
void Track::update()
{
    qreal lastX = startX;
    qreal count = 0;

    deleteTactLines();
    QList<NoteGroup*> groups = sortListGroups();
    drawLines();

    for (QList<NoteGroup*>::iterator iter = groups.begin(); iter != groups.end(); ++iter)
    {
        NoteGroup* group = *iter;
        QList<QGraphicsItem*> notes = group->childItems();
        bool first = true;
        for (QList<QGraphicsItem*>::iterator iter_n = notes.begin(); iter_n != notes.end(); ++iter_n)
        {
            MusicSymbol* symbol = dynamic_cast<MusicSymbol*>(*iter_n);
            QVector<int> params = symbol->getParams();
            drawNote(symbol, lastX);

            if (first && params[0] != 100)
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

        if (count >= 1.0f)
        {
            lastX += notes.first()->boundingRect().width()*NOTE_SCALE + SPACE;
            count = 0;
            this->scene()->addLine(lastX,-SIZE,lastX,3*SIZE,pen);
        }

        lastX += notes.first()->boundingRect().width()*NOTE_SCALE + SPACE;
        if (lastX >= right)
        {
            changeLines(right + MORE_LENGTH);
        }

    }
}

//Прорисовка ключа и трековых параметров, а так же конечных символов
void Track::drawStart()
{
    //Рисуем ключ
    key->setTransformationMode(Qt::SmoothTransformation);
    key->setFlag(QGraphicsItem::ItemIsSelectable);
    key->setPos(-640,-45);
    key->setScale(KEY_SCALE);
    key->addParam(100);
    this->scene()->addItem(key);
    int lastX = key->pos().x() + key->boundingRect().width()*KEY_SCALE;

    //Рисуем размерность
    QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(params[0]));
    text->setPos(lastX + 5, -45);;
    text->setScale(TEXT_SCALE);
    this->scene()->addItem(text);

    text = new QGraphicsTextItem(QString::number(params[1]));
    text->setPos(lastX + 5, -15);
    text->setScale(TEXT_SCALE);
    this->scene()->addItem(text);
    lastX += text->boundingRect().width()*TEXT_SCALE + SPACE;
    startX = lastX;


    end->setTransformationMode(Qt::SmoothTransformation);
    end->setFlag(QGraphicsItem::ItemIsSelectable);
    end->setPos(right - end->boundingRect().width()*END_SCALE + 2,-15);
    end->setScale(END_SCALE);
    end->addParam(100);
    this->scene()->addItem(end);
}

//Создание ноты
void Track::createNote(const QString& str)
{
    int id = str.toInt();
    NoteGroup* group = new NoteGroup;
    MusicSymbol* symbol = new MusicSymbol(this, pixVect[NOTE_START+id], group);
    symbol->addParam(0);
    symbol->addParam(id);

    symbol->setTransformationMode(Qt::SmoothTransformation);
    symbol->setScale(NOTE_SCALE);
    symbol->setX(right);
    symbol->setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    symbol->setFlag(QGraphicsItem::ItemIsFocusable);
    symbol->setFlag(QGraphicsItem::ItemIsSelectable);
    this->scene()->addItem(group);

    update();
}

void Track::setSelectRect(qreal x, qreal y, qreal w, qreal h)
{
    selectRect->setRect(x,y,w,h);
}

QGraphicsRectItem* Track::getSelectRect()
{
    return selectRect;
}

Track::~Track()
{
    pixVect.clear();
}
