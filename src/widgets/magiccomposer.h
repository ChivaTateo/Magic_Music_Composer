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
    void closeEvent(QCloseEvent *);
public slots:
    void on_exit_triggered();
private:
    QSignalMapper* noteMapper;
    QSignalMapper* pauseMapper;
    QSignalMapper* taktMapper;

    Ui::MagicComposer *ui;
};

#endif // MAINWINDOW_H
