#ifndef PROJECTVIEWER_H
#define PROJECTVIEWER_H

#include <QTabWidget>
#include "trackviewer.h"

class ProjectViewer : public QTabWidget
{
    Q_OBJECT
public:
    explicit ProjectViewer(QWidget *parent = 0);

signals:

public slots:
    void addTrack();
    void addProject();
};

#endif // PROJECTVIEWER_H
