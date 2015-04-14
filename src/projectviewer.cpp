#include "projectviewer.h"

ProjectViewer::ProjectViewer(QWidget *parent) :
    QTabWidget(parent)
{
}

void ProjectViewer::addTrack()
{
    TrackViewer* viewer = dynamic_cast<TrackViewer*>(this->currentWidget());
    viewer->addTrack();

}

void ProjectViewer::addProject()
{
    TrackViewer* viewer  = new TrackViewer(this);
    this->addTab(viewer, "Проект");
    this->setCurrentWidget(viewer);
    viewer->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
}

void ProjectViewer::createNote(int id)
{
    TrackViewer* viewer = dynamic_cast<TrackViewer*>(this->currentWidget());
    QList<Track*> tracks = viewer->getTracks();

    for(QList<Track*>::iterator iter = tracks.begin(); iter != tracks.end(); ++iter)
    {
        if (Track::lastFocus == *iter)
        {
            (*iter)->createNote(id);
            (*iter)->setFocus();
        }
    }
}
