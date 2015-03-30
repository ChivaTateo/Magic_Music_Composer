#ifndef NOTEPAINTER_H
#define NOTEPAINTER_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtCore>

class NotePainter : public QGraphicsView
{
    Q_OBJECT
public:
    explicit NotePainter(QWidget *parent = 0);

signals:

public slots:

};

#endif // NOTEPAINTER_H
