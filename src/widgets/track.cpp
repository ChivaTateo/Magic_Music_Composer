#include "track.h"
#include "options.h"

Track* Track::lastFocus = nullptr;
QVector<QPixmap> Track::pixVect;
bool Track::ctrl = false;

Track::Track(QWidget *parent) :
    QGraphicsView(parent)
{
    this->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    this->setScene(new QGraphicsScene());

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
    map.load(QCoreApplication::applicationDirPath() + "/images/pause4.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/pause5.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/pause6.png");
    pixVect.append(map);

    map.load(QCoreApplication::applicationDirPath() + "/images/end1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/end2.png");
    pixVect.append(map);

    map.load(QCoreApplication::applicationDirPath() + "/images/spec1_1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/spec1_2.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/spec2_1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/spec2_2.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/spec3_1.png");
    pixVect.append(map);
    map.load(QCoreApplication::applicationDirPath() + "/images/spec3_2.png");
    pixVect.append(map);

    setMouseTracking(true);

    //Создание кисти для курсора и самого курсора
    QBrush newBrush(Qt::blue);

    selectRect = new QGraphicsRectItem(0,0,0,0);
    selectRect->setBrush(newBrush);
    selectRect->setOpacity(0.1);
    this->scene()->addItem(selectRect);

    key = new Key(this, pixVect[0]);
    key->addParam(0);
    end = new End(this, pixVect[END_START]);
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

//Обновление виджета и координат нот
void Track::update()
{
    qreal lastX = 0;
    if (key->getParams()[0] == 1)
        key->setPos(-650,-1.5*SIZE_BETWEEN_LINES);
    else
        key->setPos(-650,-3*SIZE_BETWEEN_LINES);
    lastX = key->pos().x() + key->boundingRect().width()*KEY_SCALE;
    text_1->setPos(lastX + 5, -3*SIZE_BETWEEN_LINES);
    text_2->setPos(lastX + 5, -SIZE_BETWEEN_LINES);
    lastX += text_2->boundingRect().width()*TEXT_SCALE + SPACE;

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
            MusicSymbol* symbol = static_cast<MusicSymbol*>(*iter_n);
            QVector<int> params = symbol->getParams();
            symbol->drawSymbol(lastX,pen);

            if (first)
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
            }

        }

        if (count >= 1)
        {
            lastX += notes.first()->boundingRect().width()*NOTE_SCALE + SPACE;
            count = 0;
            this->scene()->addLine(lastX,-SIZE_BETWEEN_LINES,lastX,3*SIZE_BETWEEN_LINES,pen);
        }

        lastX += notes.first()->boundingRect().width()*NOTE_SCALE + SPACE;
        if (lastX >= right)
        {
            changeLines(right + MORE_LENGTH);
        }

    }

    end->setPos(right - end->boundingRect().width()*END_SCALE + 2,-SIZE_BETWEEN_LINES);
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
    text_1 = new QGraphicsTextItem(QString::number(params[0]));
    text_1->setPos(lastX + 5, -3*SIZE_BETWEEN_LINES);;
    text_1->setScale(TEXT_SCALE);
    this->scene()->addItem(text_1);

    text_2 = new QGraphicsTextItem(QString::number(params[1]));
    text_2->setPos(lastX + 5, -SIZE_BETWEEN_LINES);
    text_2->setScale(TEXT_SCALE);
    this->scene()->addItem(text_2);

    end->setTransformationMode(Qt::SmoothTransformation);
    end->setPos(right - end->boundingRect().width()*END_SCALE + 2,-SIZE_BETWEEN_LINES);
    end->setScale(END_SCALE);
    this->scene()->addItem(end);
}

//Создание ноты
void Track::createNote(int id)
{
    NoteGroup* group = new NoteGroup;
    Note* note = new Note(this, pixVect[NOTE_START+id], group);
    note->addParam(id);
    note->setX(right);
    this->scene()->addItem(group);

    update();
}

void Track::createPause(int id)
{
    NoteGroup* group = new NoteGroup;
    Pause* pause = new Pause(this, pixVect[PAUSE_START+id], group);
    pause->addParam(id);
    pause->setX(right);
    this->scene()->addItem(group);

    update();
}

void Track::focusInEvent(QFocusEvent *event)
{
    event->accept();
    QBrush brush(Qt::white);
    this->scene()->setBackgroundBrush(brush);
    lastFocus = this;
    Options::p_instance->updateData(QList<MusicSymbol*>());
}

void Track::focusOutEvent(QFocusEvent *event)
{
    event->accept();
    QBrush brush(QColor(0,0,255,25));
    this->scene()->setBackgroundBrush(brush);
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
    if (i < 2)
    {
        text_1->setPlainText(QString::number(params[0]));
        text_2->setPlainText(QString::number(params[1]));
    }
}

Track::~Track()
{
    pixVect.clear();
}
