#include "magiccomposer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MagicComposer w;
    w.showMaximized();

    return a.exec();
}
