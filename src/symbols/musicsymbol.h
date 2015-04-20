#ifndef MUSICSYMBOL_H
#define MUSICSYMBOL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCore>
#include <QMessageBox>
#include <QVector>

#define PAUSE_SCALE 0.6
#define KEY_SCALE 0.9
#define TEXT_SCALE 4
#define END_SCALE 0.5
#define NOTE_SCALE 0.5
#define SPEC_SCALE 0.8

#define NOTE_SCALE_FOR_CENTER 0.25
#define LONG_NOTE_SCALE_FOR_CENTER 0.43

#define SPACE 30      //Расстояние между символами
#define HALF_SIZE 7.5 //Половина расстояния между линиями
#define SIZE_BETWEEN_LINES 15       //Расстояние между линиями
#define MORE_LENGTH 500 //Удлинение линии


class Track;

class MusicSymbol : public QGraphicsPixmapItem
{
public:
    explicit MusicSymbol(QGraphicsItem *parent = 0);
    explicit MusicSymbol(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    //Получить параметры
    QVector<int> getParams();

    //Добавить новый параметр
    void addParam(int param);

    //Изменить i-й параметр на param
    void changeParam(int param, int i);

    //Рисование ноты
    virtual void drawSymbol(qreal &lastX, QPen pen) = 0;

    ~MusicSymbol();
protected:
    QVector<int> params;    //Параметры символа. Подробное описание будет в документации
    Track* track;           //Указатель на трек, в котором находится символ.

    //Обработка нажатия мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    //Удаление ноты
    void deleteSymbol();
};

#endif // MUSICSYMBOL_H
