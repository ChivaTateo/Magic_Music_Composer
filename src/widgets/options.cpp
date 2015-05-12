#include "options.h"
#include "ui_note_options.h"
#include "ui_pause_options.h"
#include "ui_track_options.h"

Options* Options::p_instance = nullptr;

Options::Options(QWidget *parent) :
    QWidget(parent),
    note_ui(new Ui::Note_Options),
    pause_ui(new Ui::Pause_Options),
    track_ui(new Ui::Track_Options)
{
    p_instance = this;
    mapper = new QSignalMapper(this);
}

void Options::deleteUi()
{
    QObjectList list = this->children();

    for (QObjectList::iterator iter = list.begin(); iter != list.end(); ++iter)
    {
        delete *iter;
    }
}

void Options::updateData(QList<MusicSymbol*> symbols)
{
    deleteUi();

    this->symbols = symbols;

    if (symbols.isEmpty())
    {
        loadTrackOptions();
    }
    else if (symbols.size() == 1)
    {
        Note* note = dynamic_cast<Note*>(symbols.first());
        if (note != nullptr)
        {
            loadNoteOptions();
        }
        else
        {
            Pause* pause = dynamic_cast<Pause*>(symbols.first());
            if (pause != nullptr)
            {
                loadPauseOptions();
            }
        }
    }
}

void Options::changeNotePixmap(int id)
{
    symbols.first()->changeParam(id, 1);
    note_ui->note_pixmap->setPixmap(QPixmap(":/notes/"+QString::number(id)));
    Track::lastFocus->update();
}

void Options::changeNoteParams()
{
    Note* note = static_cast<Note*>(symbols.first());

    if (note->getParams().size() > 2)
    {
        note->changeParam(idRadioButton(),2);
    }
    else
    {
        note->addSpec(idRadioButton());
    }

    Track::lastFocus->update();
}

int Options::idRadioButton()
{
    if(note_ui->rBut_flat->isChecked())
        return 0;
    else if(note_ui->rBut_nat->isChecked())
        return 1;
    else if(note_ui->rBut_sharp->isChecked())
        return 2;
    else
        return 0;
}

void Options::changeTrackParams()
{
    Track::lastFocus->getEnd()->changeParam(track_ui->end_slider->value(),0);
    Track::lastFocus->getEnd()->setPixmap(QPixmap(":/ends/"+QString::number(track_ui->end_slider->value())));
    track_ui->end_pixmap->setPixmap(QPixmap(":/ends/"+QString::number(track_ui->end_slider->value())));

    Track::lastFocus->getKey()->changeParam(track_ui->key_slider->value(),0);
    Track::lastFocus->getKey()->setPixmap(QPixmap(":/keys/"+QString::number(track_ui->key_slider->value())));
    track_ui->key_pixmap->setPixmap(QPixmap(":/keys/"+QString::number(track_ui->key_slider->value())));

    Track::lastFocus->changeParam(track_ui->size_slider->value(),0);
    Track::lastFocus->changeParam(track_ui->tones_cb->currentIndex(),1);

    Track::lastFocus->update();
}

void Options::changePauseParams(int id)
{
    symbols.first()->changeParam(id, 0);
    pause_ui->pause_pixmap->setPixmap(QPixmap(":/pauses/"+QString::number(id)));
    Track::lastFocus->update();
}

Options::~Options()
{
    delete note_ui;
    delete pause_ui;
    delete track_ui;
    p_instance = nullptr;
}

void Options::clear_clicked()
{
    Note* note = static_cast<Note*>(symbols.first());
    note->clear();
    Track::lastFocus->update();
}

void Options::delete_clicked()
{
    symbols.first()->deleteSymbol();
    Track::lastFocus->update();
}

void Options::loadTrackOptions()
{
    track_ui->setupUi(this);
    track_ui->size_slider->setValue(Track::lastFocus->getParams()[0]);
    track_ui->size_slider->setMaximum(4);

    track_ui->key_pixmap->setPixmap(QPixmap(":/keys/" + QString::number(Track::lastFocus->getKey()->getParams()[0])));
    track_ui->key_slider->setValue(Track::lastFocus->getKey()->getParams()[0]);
    track_ui->key_slider->setMaximum(1);

    track_ui->end_pixmap->setPixmap(QPixmap(":/ends/" + QString::number(Track::lastFocus->getEnd()->getParams()[0])));
    track_ui->end_slider->setValue(Track::lastFocus->getEnd()->getParams()[0]);
    track_ui->end_slider->setMaximum(1);

    track_ui->tones_cb->setCurrentIndex(Track::lastFocus->getParams()[1]);

    connect(track_ui->key_slider,SIGNAL(valueChanged(int)),this,SLOT(changeTrackParams()));
    connect(track_ui->end_slider,SIGNAL(valueChanged(int)),this,SLOT(changeTrackParams()));
    connect(track_ui->size_slider,SIGNAL(valueChanged(int)),this,SLOT(changeTrackParams()));
    connect(track_ui->tones_cb,SIGNAL(currentIndexChanged(int)),this,SLOT(changeTrackParams()));
}

void Options::loadNoteOptions()
{
    note_ui->setupUi(this);
    note_ui->note_pixmap->setPixmap(symbols.first()->pixmap());
    note_ui->note_slider->setValue(symbols.first()->getParams()[1]);
    note_ui->note_slider->setMaximum(7);

    if (symbols.first()->getParams().size() > 2)
    {
        switch(symbols.first()->getParams()[2])
        {
            case 0:
                note_ui->rBut_flat->setChecked(true);
                break;
            case 1:
                note_ui->rBut_nat->setChecked(true);
                break;
            case 2:
                note_ui->rBut_sharp->setChecked(true);
                break;
        }
    }

    connect(note_ui->but_clear,SIGNAL(clicked()),this,SLOT(clear_clicked()));
    connect(note_ui->but_delete,SIGNAL(clicked()),this,SLOT(delete_clicked()));
    connect(note_ui->note_slider,SIGNAL(valueChanged(int)),this,SLOT(changeNotePixmap(int)));

    connect(note_ui->rBut_flat,SIGNAL(clicked()),this,SLOT(changeNoteParams()));
    connect(note_ui->rBut_nat,SIGNAL(clicked()),this,SLOT(changeNoteParams()));
    connect(note_ui->rBut_sharp,SIGNAL(clicked()),this,SLOT(changeNoteParams()));
}

void Options::loadPauseOptions()
{
    pause_ui->setupUi(this);
    pause_ui->pause_pixmap->setPixmap(symbols.first()->pixmap());
    pause_ui->pause_slider->setValue(symbols.first()->getParams()[0]);
    pause_ui->pause_slider->setMaximum(5);

    connect(pause_ui->pause_slider,SIGNAL(valueChanged(int)),this,SLOT(changePauseParams(int)));
    connect(pause_ui->but_delete,SIGNAL(clicked()),this,SLOT(delete_clicked()));
}
