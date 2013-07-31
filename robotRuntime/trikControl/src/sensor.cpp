#include "sensor.h"

#include <QtCore/QDataStream>

#include <QtCore/QDebug>

using namespace trikControl;

void Sensor::init(QString const &controlFile)
{
	mControlFile.setFileName(controlFile);
}

int Sensor::read()
{
	if (mControlFile.open(QIODevice::ReadOnly)) {
		QDataStream stream(&mControlFile);
		int value = 0;
		stream >> value;
		mControlFile.close();

		qDebug() << "read, reading: " << value;

		return value;
	}

	qDebug() << "read, reading failed, file name: " << mControlFile.fileName();

	return 0;
}
