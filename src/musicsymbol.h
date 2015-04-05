#ifndef MUSICSYMBOL_H
#define MUSICSYMBOL_H

#include <QObject>
#include "QVector"

class MusicSymbol : public QObject
{
    Q_OBJECT
private:
    QVector<int> params;
public:
    explicit MusicSymbol(QObject *parent = 0):
        QObject(parent)
    {}

    QVector<int> getParams()
    {
        return params;
    }

    void addParam(int param)
    {
        params.push_back(param);
    }

    void changeParam(int param, int i)
    {
        params[i] = param;
    }

    ~MusicSymbol()
    {
        params.clear();
    }
};

#endif // MUSICSYMBOL_H
