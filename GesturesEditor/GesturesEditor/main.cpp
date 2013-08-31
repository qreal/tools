#include <QtGui>
#include <QApplication>
#include "gestEdit.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GestEdit w;
	w.show();

	return a.exec();
}
