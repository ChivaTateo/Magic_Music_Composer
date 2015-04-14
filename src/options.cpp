#include "options.h"
#include "ui_options_1.h"
#include "ui_options_2.h"

Options* Options::p_instance = nullptr;

Options::Options(QWidget *parent) :
    QWidget(parent),
    ui_1(new Ui::Options_1),
    ui_2(new Ui::Options_2)
{
    p_instance = this;
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

    if (symbols.size() == 1)
    {
        ui_1->setupUi(this);
        ui_1->label->setPixmap(symbols.first()->pixmap());
        if (symbols.first()->getParams()[1] < 100)
        {
            ui_1->verticalSlider->setMaximum(7);
            ui_1->verticalSlider->setValue(symbols.first()->getParams()[1]);
            connect(ui_1->verticalSlider,SIGNAL(valueChanged(int)), this,SLOT(changePixmap(int)));
        }
    }
}

void Options::changePixmap(int id)
{
    if (symbols.size() == 1)
    {
        if (symbols.first()->getParams()[1] < 100)
        {
            symbols.first()->changeParam(ui_1->verticalSlider->value(),1);
            ui_1->label->setPixmap(Track::pixVect[NOTE_START+id]);
            symbols.first()->setPixmap(Track::pixVect[NOTE_START+id]);
            Track* track = static_cast<Track*>(symbols.first()->scene()->views()[0]);
            track->update();
        }
    }

}

Options::~Options()
{
    delete ui_1;
    delete ui_2;
}
