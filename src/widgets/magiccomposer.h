#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QFileDialog>
#include "trackviewer.h"

namespace Ui {
class MagicComposer;
}

class MagicComposer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MagicComposer(QWidget *parent = 0);
    ~MagicComposer();
    void closeEvent(QCloseEvent *);
public slots:
    void on_exit_triggered();
    void exportTo();
    void saveProject();
    void openProject();
    void saveTrack();
    void openTrack();

private:
    QSignalMapper* noteMapper;
    QSignalMapper* pauseMapper;
    QSignalMapper* taktMapper;

    Ui::MagicComposer *ui;

    void createTrackXML(QXmlStreamWriter &xmlWriter, Track* track);
    void readTrackXML(QXmlStreamReader &xmlReader);
};

#endif // MAINWINDOW_H
