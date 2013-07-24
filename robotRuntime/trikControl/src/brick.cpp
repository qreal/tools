#include "brick.h"

#include <QtCore/QDebug>

using namespace trikControl;

Brick::Brick()
		: mMotor0(1500000, 1800000, "/sys/class/pwm/ehrpwm.1:0/duty_ns")
		, mMotor1(1500000, 1800000, "/sys/class/pwm/ehrpwm.1:1/duty_ns")
		, mSensor0("")
		, mSensor1("")
{
}

void Brick::playSound(QString const &soundFileName)
{
	qDebug() << "playSound, file: " << soundFileName;

	QString const command = "aplay --quiet " + soundFileName + " &";
	system(command.toStdString().c_str());
}

void Brick::stop()
{
	qDebug() << "stop";

	mMotor0.powerOff();
	mMotor1.powerOff();
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

	switch (port) {
	case 1:
		return &mSensor0;
	case 2:
		return &mSensor1;
	default:
		return &mSensor0;
	}
}

void Brick::wait(int const &milliseconds) const
{
	SleeperThread::msleep(milliseconds);
}
