#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include <QtNetwork/QHostAddress>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w(QHostAddress("192.168.1.1"), 1000);
	w.show();

	return a.exec();
}
