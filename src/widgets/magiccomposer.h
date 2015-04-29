#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include "track.h"

namespace Ui {
class MagicComposer;
}

class MagicComposer : public QMainWindow
{
    Q_OBJECT

public:
    explicit MagicComposer(QWidget *parent = 0);
    ~MagicComposer();

private:
    QSignalMapper* noteMapper;
    QSignalMapper* pauseMapper;
    QSignalMapper* taktMapper;

    Ui::MagicComposer *ui;
};

#endif // MAINWINDOW_H
