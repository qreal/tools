#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QFileInfo>
#include <QtCore/QDebug>

#include "folderCompressor.h"

using namespace compressor;

const QString description = QObject::tr("Utility for decompression or compression of QReal save files.");

int main(int argc, char *argv[])
{
	QCoreApplication app(argc, argv);
	QCoreApplication::setApplicationName("Compressor");
	QCoreApplication::setApplicationVersion("1.0");

	QCommandLineParser parser;
	parser.setApplicationDescription(description);
	parser.addHelpOption();
	parser.addVersionOption();

	parser.addPositionalArgument("source"
			, QObject::tr("Source file to be decompressed or directory to be compressed."));

	parser.process(app);

	const QStringList positionalArgs = parser.positionalArguments();
	if (positionalArgs.size() != 1) {
		parser.showHelp();
	}

	const QString source = positionalArgs[0];

	QFileInfo sourceFileInfo(source);

	bool success = false;

	if (sourceFileInfo.isDir()) {
		const QString target = sourceFileInfo.fileName() + ".qrs";
		success = FolderCompressor::compressFolder(source, target);
	} else if (sourceFileInfo.isFile()) {
		const QString target = sourceFileInfo.baseName();
		success = FolderCompressor::decompressFolder(source, target);
	} else {
		qDebug() << QObject::tr("Incorrect argument.");
	}

	return success ? 0 : 1;
}
