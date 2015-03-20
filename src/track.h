#ifndef TRACK_H
#define TRACK_H

#include <QObject>

class Track : public QObject
{
    Q_OBJECT
private:
    QList<QList<MusicSymbol>> notesheet;
    QVector<QString> params;

public:
    explicit Track(QObject *parent = 0);
    explicit Track(QObject *parent = 0, QList<QList<MusicSymbol>> notesheet, QVector<QString> params):
        QObject(parent),
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
