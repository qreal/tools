#include <QApplication>
#include "preferencesDialog.h"
#include "widget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    PreferencesDialog w;
//    w.init(nullptr, nullptr, nullptr, nullptr);
//    w.show();
    Widget w;
    w.init();
    w.show();

    return a.exec();
}
