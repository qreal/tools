#include <QtGui/QApplication>
#include "diagramrecognizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiagramRecognizer widget;
    widget.setGeometry(100, 100, 500, 355);
    widget.show();

    return a.exec();
}
