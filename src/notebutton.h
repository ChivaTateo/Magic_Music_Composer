#ifndef NOTEBUTTON_H
#define NOTEBUTTON_H

#include <QPushButton>
#include <QSignalMapper>

class NoteButton : public QPushButton
{
    Q_OBJECT
private:
    QSignalMapper* mapper;
public:
    explicit NoteButton(QWidget *parent = 0):QPushButton(parent)
    {
        mapper = new QSignalMapper(this);

        connect(this,SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(this, QString::number(0));
        connect(mapper, SIGNAL(mapped(const QString &)),
                this, SIGNAL(clicked(const QString &)));
    }

};
#endif // NOTEBUTTON_H
