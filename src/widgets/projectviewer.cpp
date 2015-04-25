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
        TrackViewer* viewer = static_cast<TrackViewer*>(this->currentWidget());
        QList<Track*> tracks = viewer->getTracks();

        for(QList<Track*>::iterator iter = tracks.begin(); iter != tracks.end(); ++iter)
        {
            if (Track::lastFocus == *iter)
            {
                (*iter)->createNote(id);
            }
        }
    }
}

void ProjectViewer::createPause(int id)
{
    if (this->currentIndex() != -1)
    {
        TrackViewer* viewer = static_cast<TrackViewer*>(this->currentWidget());
        QList<Track*> tracks = viewer->getTracks();

        for(QList<Track*>::iterator iter = tracks.begin(); iter != tracks.end(); ++iter)
        {
            if (Track::lastFocus == *iter)
            {
                (*iter)->createPause(id);
            }
        }
    }
}

void ProjectViewer::closeProject(int index)
{
    this->removeTab(index);
}

void ProjectViewer::exportTo()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Export File"), "",
        tr("JPG Files (*.jpg);;PNG Files (*.png);;PDF Files(*.pdf)"));

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

ProjectViewer::~ProjectViewer()
{

}
