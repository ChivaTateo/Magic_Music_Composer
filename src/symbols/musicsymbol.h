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

#define SPACE 30      //Расстояние между символами
#define HALF_SIZE 7.5 //Половина расстояния между линиями
#define SIZE_BETWEEN_LINES 15       //Расстояние между линиями
#define MORE_LENGTH 500 //Удлинение линии

#ifdef Q_OS_ANDROID
    #define TEXT_SCALE 2
    #define TEXT_Y_1 -2*SIZE_BETWEEN_LINES
    #define TEXT_Y_2 0
#else
    #define TEXT_SCALE 4
    #define TEXT_Y_1 -3*SIZE_BETWEEN_LINES
    #define TEXT_Y_2 -SIZE_BETWEEN_LINES
#endif

#define TONE_SCALE 0.45

#define NOTE_SCALE_FOR_CENTER 0.25
#define LONG_NOTE_SCALE_FOR_CENTER 0.43


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
    virtual void drawSymbol(qreal &lastX) = 0;

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
