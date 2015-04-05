#ifndef NOTEPAINTER_H
#define NOTEPAINTER_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtCore>
#include <QtGui>
#include "track.h"

class NotePainter : public QGraphicsView
{
    Q_OBJECT
public:
    explicit NotePainter(QWidget *parent = 0);
    ~NotePainter();
private:
    Track* track;
    qreal lastX;
    QVector<QPixmap> pixVect;

    void drawLines(QPen pen);
    void drawStart();
    void drawNotes(QPen pen);
signals:

public slots:
    void update();
};

#endif // NOTEPAINTER_H
