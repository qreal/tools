#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFile>

namespace scriptRunner {

class SensorProxy : public QObject
{
	Q_OBJECT

public slots:
	/// Returns current raw reading of a sensor.
	int read();
};

}
