#include "track.h"
#include "options.h"
#include "trackviewer.h"

Track* Track::lastFocus = nullptr;
bool Track::ctrl = false;

Track::Track(QWidget *parent) :
    QGraphicsView(parent)
{
    scaled = false;

    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setScene(new QGraphicsScene());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    //Первоначальные параметры трека при создании
    params.push_back(0);
    params.push_back(0);
    this->setStyleSheet( "QGraphicsView { border-style: none; }" );
    pen.setColor(Qt::black);
    pen.setWidth(3);

    setMouseTracking(true);

    //Создание кисти для курсора и самого курсора
    QBrush newBrush(Qt::blue);
    QPen cur_pen(Qt::blue);
    cursor = new QGraphicsLineItem();
    cursor->setPen(cur_pen);

    selectRect = new QGraphicsRectItem(0,0,0,0);
    selectRect->setBrush(newBrush);
    selectRect->setOpacity(0.1);
    this->scene()->addItem(selectRect);

    key = new Key(this, QPixmap(":/keys/0"));
    key->addParam(0);
    end = new End(this, QPixmap(":/ends/0"));
    end->addParam(0);

    this->setAlignment(Qt::AlignLeft);
    //Прорисовка старта
    drawLines();
    drawStart();

    connect(this->scene(),SIGNAL(selectionChanged()),this,SLOT(selectionChanged()));
}


//Первоначальная прорисовка нотоносца(линии)
void Track::drawLines()
{
    this->scene()->addLine(-650,0,500,0,pen);
    this->scene()->addLine(-650,15,500,15,pen);
    this->scene()->addLine(-650,30,500,30,pen);
    this->scene()->addLine(-650,45,500,45,pen);
    this->scene()->addLine(-650,-15,500,-15,pen);
    right = 500;
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
            line->setLine(-650,(count-2)*SIZE_BETWEEN_LINES,x,(count-2)*SIZE_BETWEEN_LINES);
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
void Track::deleteAdditLines()
{
    QList<QGraphicsItem*> items = this->scene()->items();

    for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
    {
        AdditLine* line = dynamic_cast<AdditLine*>(*iter);
        if (line != nullptr)
        {
            this->scene()->removeItem(line);
        }
    }
}

//Обновление виджета и координат нот
void Track::update()
{
    qreal lastX = 0;

    key->drawSymbol(lastX);

    for (QList<QGraphicsPixmapItem*>::iterator iter = tones.begin(); iter != tones.end(); ++iter)
    {
        this->scene()->removeItem(*iter);
    }
    tones.clear();

    if (params[1] != 0)
    {
        drawTones(lastX);
    }

    size->setPos(lastX + 5,-SIZE_BETWEEN_LINES);
    lastX += size->boundingRect().width()*SIZE_SCALE + SPACE;

    //qreal count = 0;
    deleteAdditLines();
    QList<NoteGroup*> groups = sortListGroups();
    for (QList<NoteGroup*>::iterator iter = groups.begin(); iter != groups.end(); ++iter)
    {
        NoteGroup* group = *iter;
        QList<QGraphicsItem*> notes = group->childItems();
        //bool first = true;
        for (QList<QGraphicsItem*>::iterator iter_n = notes.begin(); iter_n != notes.end(); ++iter_n)
        {
            MusicSymbol* symbol = static_cast<MusicSymbol*>(*iter_n);
            symbol->drawSymbol(lastX);

            /*if (first)
            {
                if (params.size() == 1)
                {
                    count += 1/qPow(2,params[0]+2);
                }
                else
                {
                    if(params[1] == 0)
                    {
                        count = 1.0;
                    }
                    else
                        count += 1/qPow(2,params[1]);
                }
                first = false;
            }*/

        }

        /*if (count >= 1)
        {
            lastX += notes.first()->boundingRect().width()*NOTE_SCALE + SPACE;
            count = 0;
            TaktLine* takt =  new TaktLine(lastX,-SIZE_BETWEEN_LINES,lastX,3*SIZE_BETWEEN_LINES,pen);
            this->scene()->addItem(takt);
        }*/

        lastX += notes.first()->boundingRect().width()*NOTE_SCALE + SPACE;
        if (lastX >= right)
        {
            changeLines(right + MORE_LENGTH);
        }

    }

    lastX = right;
    end->drawSymbol(lastX);
    this->scene()->advance();
}

//Прорисовка ключа и трековых параметров, а так же конечных символов
void Track::drawStart()
{
    //Рисуем ключ
    key->setTransformationMode(Qt::SmoothTransformation);
    key->setPos(-640,-45);
    key->setScale(KEY_SCALE);
    this->scene()->addItem(key);
    int lastX = key->pos().x() + key->boundingRect().width()*KEY_SCALE;

    //Рисуем размерность
    size = new QGraphicsPixmapItem(QPixmap(":/sizes/0"));
    size->setTransformationMode(Qt::SmoothTransformation);
    size->setScale(SIZE_SCALE);
    size->setPos(lastX + 5,-SIZE_BETWEEN_LINES);
    this->scene()->addItem(size);

    end->setTransformationMode(Qt::SmoothTransformation);
    end->setPos(right - end->boundingRect().width()*END_SCALE + 2,-SIZE_BETWEEN_LINES);
    end->setScale(END_SCALE);
    this->scene()->addItem(end);

    lastX += size->boundingRect().width()*SIZE_SCALE + SPACE;
    cursor->setLine(lastX, 45, lastX, -15);
    this->scene()->addItem(cursor);
}

//Создание ноты
void Track::createNote(int id)
{
    NoteGroup* group = new NoteGroup;
    Note* note = new Note(this, QPixmap(":/notes/"+QString::number(id)), group);
    note->addParam(id);
    note->setX(cursor->line().x1());
    this->scene()->addItem(group);

    update();

    cursor->setLine(note->x()+note->boundingRect().width()*NOTE_SCALE,45,note->x()+note->boundingRect().width()*NOTE_SCALE,-15);
    this->centerOn(cursor);
}

void Track::createPause(int id)
{
    NoteGroup* group = new NoteGroup;
    Pause* pause = new Pause(this, QPixmap(":/pauses/"+QString::number(id)), group);
    pause->addParam(id);
    pause->setX(cursor->line().x1());
    this->scene()->addItem(group);

    update();

    cursor->setLine(pause->x()+pause->boundingRect().width()*PAUSE_SCALE,45,pause->x()+pause->boundingRect().width()*PAUSE_SCALE,-15);
    this->centerOn(cursor);
}

void Track::createTakt(int id)
{
    NoteGroup* group = new NoteGroup;
    TaktLine* takt = new TaktLine(this, QPixmap(":/takts/" + QString::number(id)),group);
    takt->addParam(id);
    takt->setX(cursor->line().x1());
    this->scene()->addItem(group);

    update();

    cursor->setLine(takt->x()+takt->boundingRect().width(),45,takt->x()+takt->boundingRect().width(),-15);
    this->centerOn(cursor);
}

QPen Track::getPen()
{
    return pen;
}

void Track::focusInEvent(QFocusEvent *event)
{
    QGraphicsView::focusInEvent(event);
    TrackViewer* viewer = static_cast<TrackViewer*>(this->parent());
    viewer->focusChange();

    QBrush brush(Qt::white);
    this->scene()->setBackgroundBrush(brush);
    lastFocus = this;
    if (event->reason() == Qt::MouseFocusReason)
        Options::p_instance->updateData(QList<MusicSymbol*>());
}

void Track::setSelectRect(qreal x, qreal y, qreal w, qreal h)
{
    selectRect->setRect(x,y,w,h);
}

QGraphicsRectItem* Track::getSelectRect()
{
    return selectRect;
}

void Track::selectionChanged()
{
    QList<QGraphicsItem*> notes = this->scene()->selectedItems();
    QList<MusicSymbol*> symbols;
    for (QList<QGraphicsItem*>::iterator iter = notes.begin(); iter != notes.end(); ++iter)
    {
        MusicSymbol* symbol = dynamic_cast<MusicSymbol*>(*iter);

        if (symbol != nullptr)
        {
            symbols << symbol;
        }
    }

    Options::p_instance->updateData(symbols);
}

void Track::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        ctrl = true;
    else if (event->key() == Qt::Key_Delete)
    {
        QList<QGraphicsItem*> items = this->scene()->selectedItems();

        for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
        {
            MusicSymbol* symbol = static_cast<MusicSymbol*>(*iter);
            symbol->deleteSymbol();
        }
        this->update();
    }
}

void Track::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Control)
        ctrl = false;
}

void Track::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    QLineF line = cursor->line();

    QPointF magicPoint = mapToScene(event->pos());
    cursor->setLine(magicPoint.x(), 45, magicPoint.x(), -15);
    if (magicPoint.x() > right)
    {
        cursor->setLine(line);
    }
    else
    {
        QList<QGraphicsItem*> items = cursor->collidingItems();
        for (QList<QGraphicsItem*>::iterator iter = items.begin(); iter != items.end(); ++iter)
        {
            MusicSymbol* symbol = dynamic_cast<MusicSymbol*>(*iter);
            if (symbol != nullptr)
            {
                cursor->setLine(line);
                break;
            }
        }
    }
}

void Track::mouseDoubleClickEvent(QMouseEvent *event)
{
    QGraphicsView::mouseDoubleClickEvent(event);

    scaled = !scaled;
    if(scaled)
    {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        this->scale(1.6,1.6);
        this->centerOn(cursor);
    }
    else
    {
        this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        this->scale(0.625,0.625);
        this->centerOn(cursor);
    }

    TrackViewer* viewer = static_cast<TrackViewer*>(this->parent());
    viewer->scaleTrack(scaled);
}

End* Track::getEnd()
{
    return end;
}

Key* Track::getKey()
{
    return key;
}

QVector<int> Track::getParams()
{
    return params;
}

void Track::changeParam(int param, int i)
{
    params[i] = param;
    drawSize();
}

void Track::drawSize()
{
    switch(params[0])
    {
        case 0:
            size->setPixmap(QPixmap(":/sizes/0"));
            break;
        case 1:
            size->setPixmap(QPixmap(":/sizes/1"));
            break;
        case 2:
            size->setPixmap(QPixmap(":/sizes/2"));
            break;
        case 3:
            size->setPixmap(QPixmap(":/sizes/3"));
            break;
        case 4:
            size->setPixmap(QPixmap(":/sizes/4"));
            break;
    }
}

void Track::drawTones(qreal &lastX)
{
    bool sharp = (params[1] % 2)  == 1;
    QPixmap pixmap;
    if (sharp)
        pixmap.load(":/special/2");
    else
        pixmap.load(":/special/0");

    QVector<int> toneMap = createToneMap(sharp);
    int count = toneCount(sharp);

    for (int i = 0; i < count; ++i)
    {
        QGraphicsPixmapItem* tone = new QGraphicsPixmapItem(pixmap);
        tones.append(tone);
        tone->setScale(SPEC_SCALE*NOTE_SCALE);
        if (!sharp)
        {
            tone->setPos(lastX,
                         toneMap[i]*HALF_SIZE - tone->boundingRect().height()*SPEC_SCALE*NOTE_SCALE);
        }
        else
        {
            tone->setPos(lastX,
                         toneMap[i]*HALF_SIZE - tone->boundingRect().height()*SPEC_SCALE*TONE_SCALE);
        }

        lastX += tone->boundingRect().width()*SPEC_SCALE*NOTE_SCALE;
        tone->setTransformationMode(Qt::SmoothTransformation);
        this->scene()->addItem(tone);
    }
}

int Track::toneCount(bool sharp)
{
    int res = 0;
    if (sharp)
    {
        for(int i = -1; i != params[1]; i+=2)
        {
            ++res;
        }
    }
    else
    {
        for(int i = 0; i != params[1]; i+=2)
        {
            ++res;
        }
    }
    return res;
}

QVector<int> Track::createToneMap(bool sharp)
{
    QVector<int> map;

    if (sharp)
    {
        map.append(0);
        map.append(3);
        map.append(-1);
        map.append(2);
        map.append(5);
        map.append(1);
        map.append(4);
    }
    else
    {
        map.append(4);
        map.append(1);
        map.append(5);
        map.append(2);
        map.append(6);
        map.append(3);
        map.append(7);
    }

    return map;
}

Track::~Track()
{
}
