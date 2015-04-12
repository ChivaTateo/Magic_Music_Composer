#ifndef MUSICSYMBOL_H
#define MUSICSYMBOL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCore>
#include <QMessageBox>
#include "QVector"

#define KEY_SCALE 0.9
#define TEXT_SCALE 4
#define NOTE_SCALE 0.5
#define END_SCALE 0.5
#define NOTE_SCALE_FOR_CENTER 0.25
#define LONG_NOTE_SCALE_FOR_CENTER 0.43

class Track;

class MusicSymbol : public QGraphicsPixmapItem
{
private:
    QVector<int> params;    //Параметры символа. Подробное описание будет в документации
    static bool ctrl;       //Нажат ли CTRL
    Track* track;           //Указатель на трек, в котором находится символ.
public:
    explicit MusicSymbol(QGraphicsItem *parent = 0);
    explicit MusicSymbol(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    //Получить параметры
    QVector<int> getParams();

    //Добавить новый параметр
    void addParam(int param);

    //Изменить i-й параметр на param
    void changeParam(int param, int i);
    ~MusicSymbol();
protected:
    //Обработка движения мыши с зажатой кнопкой
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

    //Обработка отпускания мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    //Обработка нажатия мыши
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //Обработка клавиш
    void keyPressEvent(QKeyEvent *event);

    //Обработка отпускания клавиш
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MUSICSYMBOL_H
