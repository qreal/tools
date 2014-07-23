#include <QtCore/QCoreApplication>

#include "argsParser.h"
#include "worker.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	ArgsParser const args(a.arguments());
	if (args.helpMode()) {
		PRINT(args.helpText());
		return 0;
	}

	Worker worker(args.logFilePath(), args.applicationPath(), args.startupArgs(), args.speed());
	worker.go();
	return a.exec();
}
