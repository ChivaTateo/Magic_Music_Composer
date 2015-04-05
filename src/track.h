#ifndef TRACK_H
#define TRACK_H

#include <QObject>
#include <QtCore>
#include "musicsymbol.h"

class Track : public QObject
{
    Q_OBJECT
private:
    QList<QList<MusicSymbol*>> notesheet;
    QVector<int> params;

public:
    explicit Track(QObject *parent = 0):
        QObject(parent)
    {
    }

    QList<QList<MusicSymbol*>> getNotes()
    {
        return notesheet;
    }

    QVector<int> getParams()
    {
        return params;
    }

    void setNotes(QList<QList<MusicSymbol*>> notesheet)
    {
        this->notesheet = notesheet;
    }

    void initTest()
    {
        params.push_back(2);
        params.push_back(4);

        for (int i = 0; i < 16; ++i)
        {
            MusicSymbol* temp = new MusicSymbol;
            temp->addParam(qrand()%12 - 4);
            temp->addParam(qrand()%5);
            QList<MusicSymbol*> tempList;
            tempList.append(temp);

            if (qrand()%3 == 2)
            {
                temp = new MusicSymbol;
                temp->addParam(qrand()%12 - 4);
                temp->addParam(qrand()%5);
                tempList.append(temp);
            }
            notesheet.append(tempList);
        }
    }

    ~Track()
    {
        params.clear();
        notesheet.clear();
    }

};

#endif // TRACK_H
