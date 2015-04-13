#include "test.h"
#include "ui_test.h"

Test::Test(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Test)
{
    ui->setupUi(this);

    noteMapper = new QSignalMapper(this);

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

    connect(noteMapper, SIGNAL(mapped(const QString &)),
            ui->track, SLOT(createNote(const QString &)));

}

Test::~Test()
{
    delete ui;
}
