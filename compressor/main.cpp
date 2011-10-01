#include <QtCore/QCoreApplication>
#include "folderCompressor.h"


int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QString sDir = qApp->applicationDirPath();
	QDir dir(sDir);
	QString fileName = dir.dirName();
	FolderCompressor().compressFolder(sDir + "/save", sDir + "/" + fileName + ".qrs");
}
