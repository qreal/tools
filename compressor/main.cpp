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

	parser.addPositionalArgument("target"
			, QObject::tr(
					"Target directory for a file to be decompressed to or file for a directory to be compressed to."
			));

	parser.process(app);

	const QStringList positionalArgs = parser.positionalArguments();
	if (positionalArgs.size() != 2) {
		parser.showHelp();
	}

	const QString source = positionalArgs[0];
	const QString target = positionalArgs[1];

	QFileInfo sourceFileInfo(source);
	QFileInfo targetFileInfo(target);

	bool success = false;

	if (sourceFileInfo.isDir() && (targetFileInfo.isFile() || !targetFileInfo.exists())) {
		success = FolderCompressor::compressFolder(source, target);
	} else if (sourceFileInfo.isFile() && (targetFileInfo.isDir() || !targetFileInfo.exists())) {
		success = FolderCompressor::decompressFolder(source, target);
	} else {
		qDebug() << QObject::tr("One of the arguments must be a file, one must be a folder.");
	}

	return success ? 0 : 1;
}
