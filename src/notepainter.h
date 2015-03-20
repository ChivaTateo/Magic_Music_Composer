#ifndef NOTEPAINTER_H
#define NOTEPAINTER_H

#include <QWidget>
#include <QPainter>

class NotePainter : public QPainter
{
    Q_OBJECT
public:
    explicit NotePainter(QWidget *parent = 0);

signals:

public slots:

};

#endif // NOTEPAINTER_H
