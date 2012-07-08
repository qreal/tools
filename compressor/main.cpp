#include <QtCore/QCoreApplication>
#include "folderCompressor.h"


int main(int argc, char *argv[])
{
	QString const pack = argv[1];
	QString const source = argv[2];
	QString const result = argv[3];
	QCoreApplication a(argc, argv);
	if (pack == "-pack") {
		FolderCompressor().compressFolder(source, result);
	}
	else if (pack == "-unpack"){
		FolderCompressor().decompressFolder(source, result);
	}
}
