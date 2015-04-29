#include "projectviewer.h"

ProjectViewer::ProjectViewer(QWidget *parent) :
    QTabWidget(parent)
{ 
    mapper = new QSignalMapper(this);

    connect(mapper,SIGNAL(mapped(int)),this,SLOT(closeProject(int)));

    this->addProject();
}

void ProjectViewer::addTrack()
{
    if (this->currentIndex() != -1)
    {
        TrackViewer* viewer = static_cast<TrackViewer*>(this->currentWidget());
        viewer->addTrack();
    }
}

void ProjectViewer::addProject()
{
    TrackViewer* viewer  = new TrackViewer(this);
    this->addTab(viewer, "Проект");
    this->setCurrentWidget(viewer);
}

void ProjectViewer::createNote(int id)
{
    if (this->currentIndex() != -1)
    {
        Track::lastFocus->createNote(id);
    }
}

void ProjectViewer::createPause(int id)
{
    if (this->currentIndex() != -1)
    {
        Track::lastFocus->createPause(id);
    }
}

void ProjectViewer::closeProject(int index)
{
    this->removeTab(index);
}

void ProjectViewer::exportTo()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"), "",
        tr("PNG Files (*.png);;PDF Files(*.pdf)"));

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

void ProjectViewer::createTakt(int id)
{
    if (this->currentIndex() != -1)
    {
        Track::lastFocus->createTakt(id);
    }
}

ProjectViewer::~ProjectViewer()
{

}

void ProjectViewer::saveProject()
{
    if (this->currentIndex() != -1)
    {
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
               TrackViewer* viewer = static_cast<TrackViewer*>(this->currentWidget());
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
    }
}

void ProjectViewer::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save track"), "",
        tr("Track Files (*.prj)"));

    if (fileName != "") {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        } else {
           this->addProject();
           QString name = fileName.split("/").last();
           this->setTabText(this->currentIndex(),name);
           QXmlStreamReader xmlReader(&file);
           readTrackXML(xmlReader);
           file.close();
        }
    }
}

void ProjectViewer::saveTrack()
{
    if (this->currentIndex() != -1)
    {
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

               createTrackXML(xmlWriter, Track::lastFocus);
               QMessageBox::warning(this,"Success","Save successed");
            }
        }
    }
}

void ProjectViewer::openTrack()
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

void ProjectViewer::createTrackXML(QXmlStreamWriter &xmlWriter, Track* track)
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

void ProjectViewer::readTrackXML(QXmlStreamReader &xmlReader)
{
    TrackViewer* viewer = static_cast<TrackViewer*>(this->currentWidget());
    Track* track;
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
