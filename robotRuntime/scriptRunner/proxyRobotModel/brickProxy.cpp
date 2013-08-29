#include "brickProxy.h"

#include <QtCore/QSettings>

#include <QtCore/QDebug>

using namespace scriptRunner;

BrickProxy::BrickProxy()
{

}

void BrickProxy::playSound(QString const &soundFileName)
{
	qDebug() << "playSound, file: " << soundFileName;

	QString const command = "aplay --quiet " + soundFileName + " &";
	system(command.toStdString().c_str());
}

void BrickProxy::stop()
{
	qDebug() << "stop";

	mMotor1.powerOff();
	mMotor2.powerOff();
	mPowerMotor1.powerOff();
	mPowerMotor2.powerOff();
	mPowerMotor3.powerOff();
	mPowerMotor4.powerOff();
}

ServoMotorProxy *BrickProxy::motor(int const &port)
{
	qDebug() << "motor, port: " << port;

	switch (port) {
	case 1:
		return &mMotor1;
	case 2:
		return &mMotor2;
	default:
		return &mMotor1;
	}
}

PowerMotor *BrickProxy::powerMotor(int const &port)
{
	qDebug() << "Power motor, port: " << port;

	switch (port) {
	case 1:
		return &mPowerMotor1;
	case 2:
		return &mPowerMotor2;
	case 3:
		return &mPowerMotor3;
	case 4:
		return &mPowerMotor4;
	default:
		return &mPowerMotor1;
	}

}

Sensor *BrickProxy::sensor(int const &port)
{
	qDebug() << "sensor, port: " << port;

	switch (port) {
	case 1:
		return &mSensor1;
	case 2:
		return &mSensor2;
	default:
		return &mSensor1;
	}
}

void BrickProxy::wait(int const &milliseconds) const
{
	SleeperThread::msleep(milliseconds);
}
