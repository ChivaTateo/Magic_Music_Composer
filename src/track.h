#ifndef NOTEPAINTER_H
#define NOTEPAINTER_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QtCore>
#include <QtGui>
#include "notegroup.h"

class Track : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Track(QWidget *parent = 0);
    ~Track();
private:
    qreal right;
    qreal count;
    qreal lastX;
    QVector<QPixmap> pixVect;
    QVector<int> params;
    QPen pen;

    void drawLines(qreal x);
    void drawStart();
signals:

public slots:
    void createNote(const QString &str);
};

#endif // NOTEPAINTER_H
