#include "magiccomposer.h"
#include "ui_magiccomposer.h"

MagicComposer::MagicComposer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagicComposer)
{
    ui->setupUi(this);
}

MagicComposer::~MagicComposer()
{
    delete ui;
}
