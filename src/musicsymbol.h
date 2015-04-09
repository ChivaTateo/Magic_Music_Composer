#ifndef MUSICSYMBOL_H
#define MUSICSYMBOL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "QVector"
#include "options.h"

class MusicSymbol : public QGraphicsPixmapItem
{
private:
    QVector<int> params;
    Options *options;
public:
    explicit MusicSymbol(QGraphicsItem *parent = 0):
        QGraphicsPixmapItem(parent)
    {}

    explicit MusicSymbol(const QPixmap &pixmap, QGraphicsItem *parent = 0):QGraphicsPixmapItem(pixmap, parent)
    {

    }

    QVector<int> getParams()
    {
        return params;
    }

    void addParam(int param)
    {
        params.push_back(param);
    }

    void changeParam(int param, int i)
    {
        params[i] = param;
    }

    ~MusicSymbol()
    {
        params.clear();
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {

        if (event->button() == Qt::MouseButton::RightButton)
        {
            options = new Options(this,0);
            options->show();

        }
    }
};

#endif // MUSICSYMBOL_H
