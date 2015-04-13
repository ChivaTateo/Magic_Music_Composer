#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    Ui::MagicComposer *ui;
};

#endif // MAINWINDOW_H