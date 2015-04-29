#ifndef PROJECTVIEWER_H
#define PROJECTVIEWER_H

#include <QTabWidget>
#include <QTabBar>
#include <QToolButton>
#include <QSignalMapper>
#include <QImage>
#include <qimage.h>
#include <QFileDialog>
#include "trackviewer.h"
#include "options.h"

class ProjectViewer : public QTabWidget
{
    Q_OBJECT
public:
    explicit ProjectViewer(QWidget *parent = 0);
    ~ProjectViewer();
public slots:
    void addTrack();
    void addProject();

    void createNote(int id);
    void createPause(int id);
    void createTakt(int id);
    void closeProject(int index);
    void exportTo();

    void saveProject();
    void openProject();
    void saveTrack();
    void openTrack();
private:
    QSignalMapper* mapper;

    void createTrackXML(QXmlStreamWriter &xmlWriter, Track* track);
    void readTrackXML(QXmlStreamReader &xmlReader);

};

#endif // PROJECTVIEWER_H
