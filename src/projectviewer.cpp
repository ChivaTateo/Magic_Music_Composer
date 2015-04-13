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
