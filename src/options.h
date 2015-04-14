#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include "track.h"

namespace Ui {
class Options_1;
class Options_2;
}

//Класс НЕ синглтон. Он просто содержит статический указатель на себя.
//Поскольку в рамках сие работы он точно будет в единственном экземпляре.
class Options : public QWidget
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

    static Options* p_instance;
    void updateData(QList<MusicSymbol*> symbols);
private slots:
    void changePixmap(int id);
private:
    QList<MusicSymbol*> symbols;

    Ui::Options_1 *ui_1;
    Ui::Options_2 *ui_2;

    void deleteUi();
};

#endif // OPTIONS_H
