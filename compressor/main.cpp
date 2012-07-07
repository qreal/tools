#include <QtCore/QCoreApplication>
#include "folderCompressor.h"
#include "QDebug"


int main(int argc, char *argv[])
{
	QString pack = argv[1];
	QString source = argv[2];
	QString result = argv[3];
	QCoreApplication a(argc, argv);
	if (pack == "-pack") {
		FolderCompressor().compressFolder(source, result);
	}
	else if (pack == "-unpack"){
		FolderCompressor().decompressFolder(source, result);
	}
}
