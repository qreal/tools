#include "brick.h"

#include <QtCore/QDebug>

using namespace trikControl;

Brick::Brick()
	: mMotor(1500000, 1800000, "/sys/class/pwm/ehrpwm.1\\:0/duty_ns")
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
	return &mMotor;
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
