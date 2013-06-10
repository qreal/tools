#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

#include "declSpec.h"

namespace trikControl {

/// Generic TRIK sensor.
class TRIKCONTROL_EXPORT Sensor : public QObject
{
	Q_OBJECT

public slots:
	/// Returns current reading of a sensor.
	int read();

};

}
