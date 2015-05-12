#ifndef PROJECTVIEWER_H
#define PROJECTVIEWER_H

#ifndef Q_OS_ANDROID
#include <QTabWidget>
#include <QTabBar>
#include <QToolButton>
#include <QSignalMapper>
#include <QImage>
#include <qimage.h>
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

private:
    QSignalMapper* mapper;

};

#endif // Q_OS_ANDROID
#endif // PROJECTVIEWER_H
