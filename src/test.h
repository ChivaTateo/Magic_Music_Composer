#ifndef TEST_H
#define TEST_H

#include <QMainWindow>
#include <QSignalMapper>

namespace Ui {
class Test;
}

class Test : public QMainWindow
{
    Q_OBJECT
private:
    QSignalMapper* mapper;
public:
    explicit Test(QWidget *parent = 0);
    ~Test();

private:
    Ui::Test *ui;
};

#endif // TEST_H
