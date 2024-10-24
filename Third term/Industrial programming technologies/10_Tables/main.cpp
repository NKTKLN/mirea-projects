#include "tables.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tables w;
    w.show();
    return a.exec();
}
