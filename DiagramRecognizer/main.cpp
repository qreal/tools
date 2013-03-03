#include <QtGui/QApplication>
#include "diagramRecognizer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DiagramRecognizer widget;
    widget.setGeometry(100, 100, 500, 355);
    widget.show();

    return a.exec();
}
