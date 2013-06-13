#include "brick.h"

#include <QtCore/QDebug>

using namespace trikControl;

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
