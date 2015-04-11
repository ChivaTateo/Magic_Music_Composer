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
    bool click;
public:
    explicit MusicSymbol(QGraphicsItem *parent = 0);
    explicit MusicSymbol(const QPixmap &pixmap, QGraphicsItem *parent = 0);

    QVector<int> getParams();
    void addParam(int param);
    void changeParam(int param, int i);
    ~MusicSymbol();
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

};
#endif // MUSICSYMBOL_H
