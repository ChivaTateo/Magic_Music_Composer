#include "magiccomposer.h"
#include "ui_magiccomposer.h"

MagicComposer::MagicComposer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagicComposer)
{
    ui->setupUi(this);

    noteMapper = new QSignalMapper(this);
    pauseMapper = new QSignalMapper(this);

    //Мап нот
    connect(ui->note_0,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_0, 0);

    connect(ui->note_1,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_1, 1);

    connect(ui->note_2,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_2, 2);

    connect(ui->note_3,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_3, 3);

    connect(ui->note_4,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_4, 4);

    connect(ui->note_5,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_5, 5);

    connect(ui->note_6,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_6, 6);

    connect(ui->note_7,SIGNAL(clicked()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->note_7, 7);

    connect(noteMapper, SIGNAL(mapped(int)),
            ui->viewer, SLOT(createNote(int)));

    //Мап пауз
    connect(ui->pause_0,SIGNAL(clicked()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->pause_0, 0);

    connect(ui->pause_1,SIGNAL(clicked()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->pause_1, 1);

    connect(ui->pause_2,SIGNAL(clicked()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->pause_2, 2);

    connect(ui->pause_3,SIGNAL(clicked()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->pause_3, 3);

    connect(ui->pause_4,SIGNAL(clicked()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->pause_4, 4);

    connect(ui->pause_5,SIGNAL(clicked()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->pause_5, 5);

    connect(pauseMapper, SIGNAL(mapped(int)),
            ui->viewer, SLOT(createPause(int)));
}

MagicComposer::~MagicComposer()
{
    delete ui;
}
