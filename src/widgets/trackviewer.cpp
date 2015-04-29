#include "trackviewer.h"

TrackViewer::TrackViewer(QWidget *parent) :
    QWidget(parent)
{
    layout = new QGridLayout(this);
    this->setLayout(layout);

    button = new QCommandLinkButton("Add Track",this);
    layout->addWidget(button,0,0,1,0);
    button->setFocusPolicy(Qt::NoFocus);
    connect(button,SIGNAL(clicked()),this,SLOT(addTrack()));

    mapper = new QSignalMapper(this);
    connect(mapper,SIGNAL(mapped(int)),this,SLOT(deleteTrack(int)));
}

void TrackViewer::addTrack()
{
    if (tracks.size() < MAX_TRACKS)
    {
        QPushButton* magic = new QPushButton(this);
        layout->addWidget(magic,tracks.size(),0);
        magic->setText("delete");
        magic->setSizePolicy(QSizePolicy(QSizePolicy::Fixed,QSizePolicy::Preferred));
        magic->setFocusPolicy(Qt::NoFocus);
        buttons.append(magic);
        connect(magic,SIGNAL(clicked()),mapper,SLOT(map()));
        mapper->setMapping(magic, tracks.size());

        Track* track = new Track(this);
        layout->addWidget(track,tracks.size(),1);
        track->setFocus();
        tracks.append(track);

        layout->addWidget(button,tracks.size()+1,0,1,0);
    }

    if (tracks.size() == MAX_TRACKS)
    {
        button->setHidden(true);
    }

}

void TrackViewer::deleteTrack(int index)
{
    bool focus = tracks.at(index)->hasFocus();

    delete tracks.at(index);
    tracks.removeAt(index);
    delete buttons.at(index);
    buttons.removeAt(index);

    for(int i = 0; i < tracks.size(); ++i)
    {
        mapper->setMapping(buttons.at(i), i);
        layout->addWidget(buttons.at(i),i,0);
        layout->addWidget(tracks.at(i),i,1);
    }
    layout->addWidget(button,tracks.size()+1,0,1,0);
    button->setHidden(false);

    if(focus && !tracks.isEmpty())
        tracks.first()->setFocus();
}

QList<Track*> TrackViewer::getTracks()
{
    return tracks;
}

void TrackViewer::scaleTrack(bool scaled)
{
     if (scaled)
     {
         int i = 0;
         for(QList<Track*>::iterator iter = tracks.begin(); iter != tracks.end(); ++iter)
         {
             if(*iter != Track::lastFocus)
             {
                 (*iter)->hide();
                 buttons.at(i)->hide();
             }
             ++i;
         }
         button->hide();
     }
     else
     {
         int i = 0;
         for(QList<Track*>::iterator iter = tracks.begin(); iter != tracks.end(); ++iter)
         {
             (*iter)->setHidden(false);
             buttons.at(i)->setHidden(false);
             ++i;
         }
         if (tracks.size() < 4)
            button->setHidden(false);
     }
}

void TrackViewer::focusChange()
{
    for(QList<Track*>::iterator iter = tracks.begin(); iter != tracks.end(); ++iter)
    {
        QBrush brush(QColor(0,0,255,25));
        (*iter)->scene()->setBackgroundBrush(brush);
    }
}

TrackViewer::~TrackViewer()
{
    tracks.clear();
    buttons.clear();
}

void TrackViewer::createNote(int id)
{
    Track::lastFocus->createNote(id);
}

void TrackViewer::createTakt(int id)
{
    Track::lastFocus->createTakt(id);
}

void TrackViewer::createPause(int id)
{
    Track::lastFocus->createPause(id);
}
