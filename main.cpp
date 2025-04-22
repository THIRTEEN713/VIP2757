#include "HomeWidge.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomeWidge w;
    w.show();
    return a.exec();
}
