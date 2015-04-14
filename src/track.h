#ifndef NOTEPAINTER_H
#define NOTEPAINTER_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtCore>
#include <QtGui>
#include "notegroup.h"

//Стартовые позиции в массиве, с которой начинаются:
#define NOTE_START 2     //ноты
#define PAUSE_START 10    //паузы
#define END_START 13     //символы конца
#define SPECIAL_START 15 //специальные символы

#define SPACE 30      //Расстояние между символами
#define HALF_SIZE 7.5 //Половина расстояния между линиями
#define SIZE 15       //Расстояние между линиями
#define MORE_LENGTH 500 //Удлинение линии

class Track : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Track(QWidget *parent = 0);
    ~Track();

    static Track* lastFocus;             //Последний трек с фокусом
    static QVector<QPixmap> pixVect;     //Массив всех иконок, необходимых для прорисовки

    //Возравращает отсортированный по X список всех блоков
    QList<NoteGroup*> sortListGroups();

    //Задает координаты "курсора" при перемещении мыши
    void setSelectRect(qreal x, qreal y, qreal w, qreal h);

    //Возвращает курсор
    QGraphicsRectItem* getSelectRect();


private:

    qreal right;            //Крайнее положение стана
    qreal startX;           //Стартовое положение для прорисовки нот

    QGraphicsRectItem* selectRect;//"Курсор" при перемещении

    QVector<int> params;    //Параметры трека. Подробное описание будет в документации
    QPen pen;               //Ручка для прорисовки линий

    MusicSymbol* key;       //Ключ
    MusicSymbol* end;       //Конечный символ


    //Рисует нотоносец(линии)
    inline void drawLines();

    //Удлиняет линии, если требуется больше
    inline void changeLines(qreal x);

    //Рисует ключ и параметры на всю строку
    void drawStart();

    //Удаляет все тактовые линии
    void deleteTactLines();

    //Изменение координат в зависимости от параметров symbol
    void drawNote(MusicSymbol* symbol, qreal lastX);

    //Событие получения и выхода из фокуса
    void focusInEvent(QFocusEvent* event);
    void focusOutEvent(QFocusEvent* event);

public slots:
    //Слот изменения выделения нот
    void selectionChanged();
    //Слот создания ноты(обработка нажатия кнопок)
    void createNote(int id);

    //Обновление всего трека
    void update();
};

#endif // NOTEPAINTER_H
