#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include "musicsymbol.h"
class Track : public QObject
{
    Q_OBJECT
private:
    QList<QList<MusicSymbol>> notesheet;
    QVector<QString> params;

public:
    explicit Track(QObject *parent = 0);

    Track(QList<QList<MusicSymbol>> notesheet, QVector<QString> params):
        notesheet(notesheet),
        params(params)
    {
    }

    QList<QList<MusicSymbol>> getNotes()
    {
        return notesheet;
    }

    void setNotes(QList<QList<MusicSymbol>> notesheet)
    {
        this->notesheet = notesheet;
    }

};

#endif // TRACK_H
