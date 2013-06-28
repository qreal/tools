#include "brick.h"

#include <QtCore/QDebug>

using namespace trikControl;

Brick::Brick()
		: mMotor0(1500000, 1800000, "/sys/class/pwm/ehrpwm.1:0/duty_ns")
		, mMotor1(1500000, 1800000, "/sys/class/pwm/ehrpwm.1:1/duty_ns")
{
}

void Brick::playSound(const QString &soundFileName)
{
	qDebug() << "playSound, file: " << soundFileName;
}

void Brick::stop()
{
	qDebug() << "stop";
}

Motor *Brick::motor(int const &port)
{
	qDebug() << "motor, port: " << port;

	switch (port) {
	case 1:
		return &mMotor0;
	case 2:
		return &mMotor1;
	default:
		return &mMotor0;
	}
}

Sensor *Brick::sensor(int const &port)
{
	qDebug() << "sensor, port: " << port;
	return &mSensor;
}

void Brick::wait(int const &milliseconds) const
{
	SleeperThread::msleep(milliseconds);
}
