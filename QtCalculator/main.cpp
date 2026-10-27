#include "QtCalculator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtCalculator w;
    w.show();
    return a.exec();
}
