#include <QtGui/QApplication>
#include "diagramrecognizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiagramRecognizer w;
    w.show();

    return a.exec();
}
