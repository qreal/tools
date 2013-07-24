#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFile>

#include "declSpec.h"

namespace trikControl {

/// Generic TRIK sensor.
class TRIKCONTROL_EXPORT Sensor : public QObject
{
	Q_OBJECT

public:
	Sensor(QString const &controlFile);

public slots:
	/// Returns current raw reading of a sensor.
	int read();

private:
	QFile mControlFile;
};

}
