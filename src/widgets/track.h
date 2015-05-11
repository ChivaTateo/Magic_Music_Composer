#ifndef TRACK_H
#define TRACK_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtCore>
#include <QtGui>

#include "../symbols/notegroup.h"
#include "../symbols/taktline.h"
#include "../symbols/additline.h"

#define SIZE_SCALE 0.6
class Track : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Track(QWidget *parent = 0);
    ~Track();

    static bool ctrl;                    //Нажат ли CTRL
    static Track* lastFocus;             //Последний трек с фокусом

    //Возравращает отсортированный по X список всех блоков
    QList<NoteGroup*> sortListGroups();

    //Задает координаты "курсора" при перемещении мыши
    void setSelectRect(qreal x, qreal y, qreal w, qreal h);
    QPen getPen();
    QGraphicsRectItem* getSelectRect();
    QVector<int> getParams();
    Key* getKey();
    End* getEnd();

    void changeParam(int param, int i);
private:
    qreal right;            //Крайнее положение стана
    bool scaled;

    QGraphicsRectItem* selectRect;   //Курсор при перемещении
    QGraphicsLineItem* cursor;       //Курсор для вставки

    QVector<int> params;    //Параметры трека. Подробное описание будет в документации
    QPen pen;               //Ручка для прорисовки линий

    Key* key;       //Ключ
    End* end;       //Конечный символ
    QGraphicsPixmapItem* size;
    QList<QGraphicsPixmapItem*> tones;

    //Рисует нотоносец(линии)
    inline void drawLines();

    //Удлиняет линии, если требуется больше
    inline void changeLines(qreal x);

    //рисует размерность
    void drawSize();
    //Рисует ключ и параметры на всю строку
    void drawStart();
    //Рисует тональность
    void drawTones(qreal &lastX);

    //Определяет точность карты
    int toneCount(bool sharp);
    //Создает карту тональности
    QVector<int> createToneMap(bool sharp);

    //Удаляет все доп. линии
    void deleteAdditLines();

    //Изменение координат в зависимости от параметров symbol
    void drawSymbol(MusicSymbol* symbol, qreal lastX);

    //Событие получения и выхода из фокуса
    void focusInEvent(QFocusEvent* event);

    //Обработка нажатия клавиш
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
public slots:
    //Слот изменения выделения нот
    void selectionChanged();
    //Слот создания ноты(обработка нажатия кнопок)
    void createNote(int id);
    //Слот создания паузы(обработка нажатия кнопок)
    void createPause(int id);
    //Слот создания такта(обработка нажатия кнопок)
    void createTakt(int id);
    //Обновление всего трека
    void update();
};

#endif // NOTEPAINTER_H
