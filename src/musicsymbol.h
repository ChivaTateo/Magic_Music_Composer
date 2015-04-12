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

class Track;

class MusicSymbol : public QGraphicsPixmapItem
{
private:
    QVector<int> params;
    static bool ctrl;
    Track* track;
public:
    explicit MusicSymbol(QGraphicsItem *parent = 0);
    explicit MusicSymbol(Track* track, const QPixmap &pixmap, QGraphicsItem *parent = 0);

    QVector<int> getParams();
    void addParam(int param);
    void changeParam(int param, int i);
    ~MusicSymbol();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};

#endif // MUSICSYMBOL_H
