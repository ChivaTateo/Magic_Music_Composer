#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>

namespace Ui {
class Options;
}

class MusicSymbol;

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    explicit Options(MusicSymbol *symbol, QWidget *parent = 0);
    ~Options();

private slots:
    void on_timeDown_clicked();

    void on_timeUp_clicked();

private:
    Ui::Options *ui;
    MusicSymbol *symbol;
};

#endif // OPTIONS_H
