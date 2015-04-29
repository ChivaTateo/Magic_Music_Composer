#include "magiccomposer.h"
#ifdef Q_OS_ANDROID
    #include "ui_magiccomposer_andr.h"
#else
    #include "ui_magiccomposer.h"
#endif

MagicComposer::MagicComposer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MagicComposer)
{
    ui->setupUi(this);

    noteMapper = new QSignalMapper(this);
    pauseMapper = new QSignalMapper(this);
    taktMapper = new QSignalMapper(this);

    //Мап нот
    connect(ui->actionNote_0,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_0, 0);

    connect(ui->actionNote_1,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_1, 1);

    connect(ui->actionNote_2,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_2, 2);

    connect(ui->actionNote_3,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_3, 3);

    connect(ui->actionNote_4,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_4, 4);

    connect(ui->actionNote_5,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_5, 5);

    connect(ui->actionNote_6,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_6, 6);

    connect(ui->actionNote_7,SIGNAL(triggered()),noteMapper,SLOT(map()));
    noteMapper->setMapping(ui->actionNote_7, 7);

    connect(noteMapper, SIGNAL(mapped(int)),
            ui->viewer, SLOT(createNote(int)));

    //Мап пауз
    connect(ui->actionPause_1,SIGNAL(triggered()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->actionPause_1, 0);

    connect(ui->actionPause_2,SIGNAL(triggered()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->actionPause_2, 1);

    connect(ui->actionPause_3,SIGNAL(triggered()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->actionPause_3, 2);

    connect(ui->actionPause_4,SIGNAL(triggered()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->actionPause_4, 3);

    connect(ui->actionPause_5,SIGNAL(triggered()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->actionPause_5, 4);

    connect(ui->actionPause_6,SIGNAL(triggered()),pauseMapper,SLOT(map()));
    pauseMapper->setMapping(ui->actionPause_6, 5);

    connect(pauseMapper, SIGNAL(mapped(int)),
            ui->viewer, SLOT(createPause(int)));

    //Мап тактов
    connect(ui->actionTakt_1,SIGNAL(triggered()),taktMapper,SLOT(map()));
    taktMapper->setMapping(ui->actionTakt_1, 0);

    connect(ui->actionTakt_2,SIGNAL(triggered()),taktMapper,SLOT(map()));
    taktMapper->setMapping(ui->actionTakt_2, 1);

    connect(ui->actionTakt_3,SIGNAL(triggered()),taktMapper,SLOT(map()));
    taktMapper->setMapping(ui->actionTakt_3, 2);

    connect(taktMapper, SIGNAL(mapped(int)),
            ui->viewer, SLOT(createTakt(int)));

    #ifdef Q_OS_ANDROID
        ui->options->hide();
        connect(ui->actionOprions,SIGNAL(triggered(bool)),ui->options,SLOT(setVisible(bool)));
    #endif
}

MagicComposer::~MagicComposer()
{
    delete ui;
}
