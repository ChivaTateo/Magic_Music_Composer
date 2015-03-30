#ifndef MUSICSYMBOL_H
#define MUSICSYMBOL_H

#include <QObject>
#include "QVector"

class MusicSymbol : public QObject
{
    Q_OBJECT
private:
    QVector<QString> params;
    unsigned short int type;

public:
    explicit MusicSymbol(QObject *parent = 0)
    {

    }

    MusicSymbol(QVector<QString> params, unsigned short int type):
        params(params),
        type(type)
    {
    }

    QVector<QString> getParams()
    {
        return params;
    }

    void setParams(QVector<QString> params)
    {
        this->params = params;
    }
};

#endif // MUSICSYMBOL_H
