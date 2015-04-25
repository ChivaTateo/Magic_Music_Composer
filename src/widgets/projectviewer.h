#ifndef PROJECTVIEWER_H
#define PROJECTVIEWER_H

#include <QTabWidget>
#include <QTabBar>
#include <QToolButton>
#include <QSignalMapper>
#include <QImage>
#include <QtPrintSupport/QPrinter>
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
    void closeProject(int index);
    void exportTo();
private:
    QSignalMapper* mapper;

};

#endif // PROJECTVIEWER_H
