#ifndef Q_OS_ANDROID

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
        if(!viewer->getTracks().isEmpty())
            Track::lastFocus->createNote(id);
    }
}

void ProjectViewer::createPause(int id)
{
    if (this->currentIndex() != -1)
    {
        TrackViewer* viewer = static_cast<TrackViewer*>(this->currentWidget());
        if(!viewer->getTracks().isEmpty())
            Track::lastFocus->createPause(id);
    }
}

void ProjectViewer::closeProject(int index)
{
    this->removeTab(index);
}

void ProjectViewer::createTakt(int id)
{
    if (this->currentIndex() != -1)
    {
        TrackViewer* viewer = static_cast<TrackViewer*>(this->currentWidget());
        if(!viewer->getTracks().isEmpty())
            Track::lastFocus->createTakt(id);
    }
}

ProjectViewer::~ProjectViewer()
{

}

#endif
