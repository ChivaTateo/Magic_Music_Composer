#ifndef MUSICSYMBOL_H
#define MUSICSYMBOL_H

#include <QObject>

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

    explicit MusicSymbol(QObject *parent = 0, QVector<QString> params, unsigned short int type):
        QObject(parent),
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
