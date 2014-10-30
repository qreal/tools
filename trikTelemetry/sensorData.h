#pragma once

#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QVector>

struct SensorData {
	QMap<QString, int> analog;
	QMap<QString, int> analogRaw;
	QMap<QString, int> digital;
	QMap<QString, int> digitalRaw;
	QMap<QString, int> special;
	QMap<QString, int> specialRaw;
	QMap<QString, int> encoders;
	QMap<QString, int> encodersRaw;
	QVector<int> accelerometer;
	QVector<int> gyroscope;
};
