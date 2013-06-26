#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QFile>

#include "declSpec.h"

namespace trikControl {

/// Generic TRIK motor.
class TRIKCONTROL_EXPORT Motor : public QObject
{
	Q_OBJECT

public:
	Motor(int powerMin, int powerMax, QString const& controlFile);

public slots:
	/// Sets current motor power to specified value, 0 to stop motor.
	/// @param power Power of a motor, from -100 (full reverse) to 100 (full forward), 0 --- stop.
	void setPower(int power);

private:
	QFile mControlFile;
	int mPowerMax;
	int mPowerMin;
};

}
