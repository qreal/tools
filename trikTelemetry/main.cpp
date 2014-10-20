#include "mainWindow.h"
#include <QtWidgets/QApplication>
#include <QtNetwork/QHostAddress>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if (argc != 3) {
		qDebug() << "Usage: trikTelemetry <ip> <update interval>";
		return 0;
	}

	QHostAddress serverAddress(a.arguments().at(1));
	bool ok;
	int updateInterval = a.arguments().at(2).toInt(&ok);

	if (serverAddress.isNull() || !ok) {
		qDebug() << "Incorrect arguments format\n"
				<< "Usage: trikTelemetry <ip> <update interval>";
		return 0;
	}

	MainWindow w(serverAddress, updateInterval);
	w.show();

	return a.exec();
}
