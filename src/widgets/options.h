#ifndef OPTIONS_H
#define OPTIONS_H

#include <QWidget>
#include <QSignalMapper>
#include "track.h"

namespace Ui {
class Note_Options;
class Pause_Options;
class Track_Options;
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
    //Слот для изменения параметров трека
    void changeTrackParams();

    //Слоты для изменения параметров нот
    void changeNoteParams();
    void changeNotePixmap(int id);
    void clear_clicked();
    void delete_clicked();

    //Слоты для изменения параметров паузы
    void changePauseParams(int id);
private:
    QList<MusicSymbol*> symbols;

    Ui::Note_Options *note_ui;
    Ui::Pause_Options *pause_ui;
    Ui::Track_Options *track_ui;

    QSignalMapper* mapper;
    void deleteUi();
    int idRadioButton();

    void loadTrackOptions();
    void loadNoteOptions();
    void loadPauseOptions();
};

#endif // OPTIONS_H
