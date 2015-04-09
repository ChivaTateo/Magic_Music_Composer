#include "options.h"
#include "ui_options.h"
#include "musicsymbol.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
}

Options::Options(MusicSymbol *symbol, QWidget *parent):QDialog(parent),ui(new Ui::Options)
{
    ui->setupUi(this);
    this->symbol = symbol;
    ui->pixmap->setPixmap(symbol->pixmap());
}

Options::~Options()
{
    delete ui;
}

void Options::on_timeDown_clicked()
{
    int param = symbol->getParams()[1];
    if(param == 0)
        return;
    else
        --param;

    symbol->changeParam(param, 1);
    symbol->update();
}

void Options::on_timeUp_clicked()
{
    int param = symbol->getParams()[1];
    if(param == 7)
        return;
    else
        ++param;

    symbol->changeParam(param, 1);
}
