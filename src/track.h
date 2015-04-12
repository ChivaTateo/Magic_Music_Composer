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
    QList<NoteGroup*> sortListGroups();
    void setSelectRect(qreal x, qreal y, qreal w, qreal h);
    QGraphicsRectItem* getSelectRect();
private:
    qreal right;
    qreal startX;
    QGraphicsRectItem* selectRect;

    QVector<QPixmap> pixVect;
    QVector<int> params;
    QPen pen;

    void drawLines();
    void changeLines(qreal x);
    void drawStart();
public slots:
    void createNote(const QString &str);
    void update();
};

#endif // NOTEPAINTER_H
