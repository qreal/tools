#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QThread>

#include "servoMotorProxy.h"
#include "powerMotorProxy.h"
#include "sensorProxy.h"

namespace scriptRunner {

class BrickProxy : public QObject
{
	Q_OBJECT

public:
	Brick();

public slots:
	/// Plays given music file on a speaker (in format accepted by aplay utility).
	void playSound(QString const &soundFileName);

	/// Stops all motors and shuts down all current activity.
	void stop();

	/// Returns reference to motor on a given port.
	Motor *motor(int const &port);

	/// Returns reference to power motor on a given port.
	PowerMotor *powerMotor(int const &port);

	/// Returns reference to sensor on a given port.
	Sensor *sensor(int const &port);

	/// Waits given amount of time in milliseconds and returns.
	void wait(int const &milliseconds) const;

private:
	class SleeperThread : public QThread
	{
	public:
		static void msleep(unsigned long msecs)
		{
			QThread::msleep(msecs);
		}
	};

	ServoMotorProxy mMotor1;
	ServoMotorProxy mMotor2;
	PowerMotorProxy mPowerMotor1;
	PowerMotorProxy mPowerMotor2;
	PowerMotorProxy mPowerMotor3;
	PowerMotorProxy mPowerMotor4;
	SensorProxy mSensor1;
	SensorProxy mSensor2;
};

}
