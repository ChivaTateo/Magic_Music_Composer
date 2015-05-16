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
        connect(ui->actionOptions,SIGNAL(triggered(bool)),ui->options,SLOT(setVisible(bool)));   
        ui->mainToolBar->setIconSize(QSize(32*QApplication::screens().first()->devicePixelRatio(),
                                           32*QApplication::screens().first()->devicePixelRatio()));


    #endif
}

MagicComposer::~MagicComposer()
{
    delete ui;
}

void MagicComposer::on_exit_triggered()
{
       if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation?",
                             "Are you sure you want to exit?",
                             QMessageBox::Yes|QMessageBox::No))
       {
            QApplication::exit();
       }
}

void MagicComposer::closeEvent(QCloseEvent *event)
{
    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation?",
                         "Are you sure you want to exit?",
                         QMessageBox::Yes|QMessageBox::No))
    {
        event->accept();
    }
}

void MagicComposer::saveProject()
{
#ifndef Q_OS_ANDROID
    if (ui->viewer->currentIndex() != -1)
    {
#endif
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save track"), "",
            tr("Project Files (*.prj)"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            } else {
               QXmlStreamWriter xmlWriter(&file);
               xmlWriter.setAutoFormatting(true);
               xmlWriter.writeStartDocument();
               xmlWriter.writeStartElement("Tracks");
#ifndef Q_OS_ANDROID
    TrackViewer* viewer = static_cast<TrackViewer*>(ui->viewer->currentWidget());
#else
    TrackViewer* viewer = ui->viewer;
#endif
               foreach(Track* track, viewer->getTracks())
               {
                   xmlWriter.writeStartElement("Track");
                   createTrackXML(xmlWriter, track);
                   xmlWriter.writeEndElement();
               }
               xmlWriter.writeEndElement();
               QMessageBox::warning(this,"Success","Save successed");
            }
        }
#ifndef Q_OS_ANDROID
    }
#endif
}

void MagicComposer::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save track"), "",
        tr("Track Files (*.prj)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        } else {
#ifndef Q_OS_ANDROID
           ui->viewer->addProject();
           QString name = fileName.split("/").last();
           ui->viewer->setTabText(ui->viewer->currentIndex(),name);
#endif
           QXmlStreamReader xmlReader(&file);
           readTrackXML(xmlReader);
           file.close();
        }
    }
}

void MagicComposer::saveTrack()
{
#ifndef Q_OS_ANDROID
    if (ui->viewer->currentIndex() != -1)
    {
#endif
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save track"), "",
            tr("Track Files (*.trk)"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            } else {
               QXmlStreamWriter xmlWriter(&file);
               xmlWriter.setAutoFormatting(true);
               xmlWriter.writeStartDocument();
               xmlWriter.writeStartElement("Track");
               createTrackXML(xmlWriter, Track::lastFocus);
               xmlWriter.writeEndElement();
               QMessageBox::warning(this,"Success","Save successed");
            }
        }
#ifndef Q_OS_ANDROID
    }
#endif
}

void MagicComposer::openTrack()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save track"), "",
        tr("Track Files (*.trk)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        } else {

           QXmlStreamReader xmlReader(&file);
           readTrackXML(xmlReader);
           file.close();
        }
    }
}

void MagicComposer::createTrackXML(QXmlStreamWriter &xmlWriter, Track* track)
{
    xmlWriter.writeStartElement("TrackData");
    xmlWriter.writeAttribute("version", "v1.0");

    xmlWriter.writeStartElement("TrackParams");
        xmlWriter.writeAttribute("size",QString::number(track->getParams()[0]));
        xmlWriter.writeAttribute("tones",QString::number(track->getParams()[1]));
    xmlWriter.writeEndElement();

    xmlWriter.writeStartElement("SymbolList");
    Key* key = track->getKey();
        xmlWriter.writeStartElement("Key");
            xmlWriter.writeAttribute("xCoord", QString::number(key->x()));
            xmlWriter.writeAttribute("yCoord", QString::number(key->y()));
            xmlWriter.writeAttribute("type",QString::number(key->getParams()[0]));
        xmlWriter.writeEndElement();  //end of Key
    End* end = track->getEnd();
        xmlWriter.writeStartElement("End");
            xmlWriter.writeAttribute("xCoord", QString::number(end->x()));
            xmlWriter.writeAttribute("yCoord", QString::number(end->y()));
            xmlWriter.writeAttribute("type",QString::number(end->getParams()[0]));
        xmlWriter.writeEndElement();  //end of End
    foreach( NoteGroup* group, track->sortListGroups())
    {
         xmlWriter.writeStartElement("NoteGroup");
             foreach(QGraphicsItem* symbol, group->childItems())
             {
                 Pause* pause = dynamic_cast<Pause*>(symbol);
                 if(pause != nullptr)
                 {
                     xmlWriter.writeStartElement("Pause");
                         xmlWriter.writeAttribute("xCoord", QString::number(pause->x()));
                         xmlWriter.writeAttribute("yCoord", QString::number(pause->y()));
                         xmlWriter.writeAttribute("type",   QString::number(pause->getParams()[0]));
                     xmlWriter.writeEndElement();
                 }
                 else
                 {
                     TaktLine* line = dynamic_cast<TaktLine*>(symbol);
                     if (line != nullptr)
                     {
                         xmlWriter.writeStartElement("TaktLine");
                             xmlWriter.writeAttribute("xCoord", QString::number(line->x()));
                             xmlWriter.writeAttribute("yCoord", QString::number(line->y()));
                             xmlWriter.writeAttribute("type",   QString::number(line->getParams()[0]));
                         xmlWriter.writeEndElement();
                     }
                     else
                     {
                         Note* note = static_cast<Note*>(symbol);
                         xmlWriter.writeStartElement("Note");
                             xmlWriter.writeAttribute("xCoord", QString::number(note->x()));
                             xmlWriter.writeAttribute("yCoord", QString::number(note->y()));
                             xmlWriter.writeAttribute("place",   QString::number(note->getParams()[0]));
                             xmlWriter.writeAttribute("type",   QString::number(note->getParams()[1]));
                             if (note->getParams().size() > 2)
                                 xmlWriter.writeAttribute("spec",   QString::number(note->getParams()[2]));
                         xmlWriter.writeEndElement();
                     }
                 }
             }
         xmlWriter.writeEndElement(); //end of NoteGroup
    }
    xmlWriter.writeEndElement();   //end of SymbolList
    xmlWriter.writeEndElement();   //end of TrackData
}

void MagicComposer::readTrackXML(QXmlStreamReader &xmlReader)
{
#ifndef Q_OS_ANDROID
    TrackViewer* viewer = static_cast<TrackViewer*>(ui->viewer->currentWidget());
#else
    TrackViewer* viewer = ui->viewer;
#endif
    Track* track = nullptr;
    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xmlReader.name() == "Track")
            {
               viewer->addTrack();
               track = viewer->getTracks().last();
            }
            else if (xmlReader.name() == "TrackParams")
            {
                track->changeParam(xmlReader.attributes().value("size").toInt(),0);
                track->changeParam(xmlReader.attributes().value("tones").toInt(),1);
            }
            else if (xmlReader.name() == "Key")
            {
                track->getKey()->changeParam(xmlReader.attributes().value("type").toInt(),0);
                track->getKey()->setPixmap(":/keys/" + QString::number(xmlReader.attributes().value("type").toInt()));
            }
            else if (xmlReader.name() == "End")
            {
                track->getEnd()->changeParam(xmlReader.attributes().value("type").toInt(),0);
                track->getEnd()->setPixmap(":/ends/" + QString::number(xmlReader.attributes().value("type").toInt()));
            }
            else if (xmlReader.name() == "NoteGroup")
            {
                NoteGroup* group = new NoteGroup;
                xmlReader.readNext();
                while(!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == "NoteGroup"))
                {
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement)
                        {
                            if (xmlReader.name() == "Pause")
                            {
                                Pause* pause = new Pause(track,
                                                         QPixmap(":/pauses/" + QString::number(xmlReader.attributes().value("type").toInt())),
                                                         group);
                                pause->addParam(xmlReader.attributes().value("type").toInt());
                                pause->setX(xmlReader.attributes().value("xCoord").toFloat());
                            }
                            else if (xmlReader.name() == "Note")
                            {
                                Note* note = new Note(track,
                                                      QPixmap(":/notes/" + QString::number(xmlReader.attributes().value("type").toInt())),
                                                      group);
                                note->changeParam(xmlReader.attributes().value("place").toInt(),0);
                                note->addParam(xmlReader.attributes().value("type").toInt());
                                if (xmlReader.attributes().hasAttribute("spec"))
                                {
                                    note->addSpec(xmlReader.attributes().value("spec").toInt());
                                }
                                note->setX(xmlReader.attributes().value("xCoord").toFloat());
                            }
                            else if (xmlReader.name() == "TaktLine")
                            {
                                TaktLine* takt = new TaktLine(track,
                                                              QPixmap(":/takts/" + QString::number(xmlReader.attributes().value("type").toInt())),
                                                              group);
                                takt->addParam(xmlReader.attributes().value("type").toInt());
                                takt->setX(xmlReader.attributes().value("xCoord").toFloat());
                            }
                        }
                     xmlReader.readNext();
                }
                track->scene()->addItem(group);
            }
        }
    }

    foreach(Track* track, viewer->getTracks())
    {
        track->update();
    }
    viewer->getTracks().last()->setFocus();
}

void MagicComposer::exportTo()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"), "",
        tr("PNG Files (*.png)"));

        if (fileName != "") {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
                return;
            } else {
                QImage* image = new QImage(Track::lastFocus->scene()->sceneRect().size().toSize(), QImage::Format_ARGB32);
                QPainter painter(image);
                painter.setRenderHint(QPainter::Antialiasing);

                Track::lastFocus->scene()->render(&painter);
                image->save(fileName);
            }
        }

}
