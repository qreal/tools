#include "mainWindow.h"

#include <QtWidgets/QApplication>
#include <QtNetwork/QHostAddress>
#include <QtCore/QTranslator>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	if (argc != 3) {
		qDebug() << "Usage: trikTelemetry <ip> <update interval>";
		return 0;
	}

	if (QLocale::system().language() == QLocale::Russian) {
		QTranslator *translator = new QTranslator;
		translator->load("trikTelemetry_ru");
		a.installTranslator(translator);
	}

	QHostAddress serverAddress(a.arguments().at(1));
	bool ok = false;
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
