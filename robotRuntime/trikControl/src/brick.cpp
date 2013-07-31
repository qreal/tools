#include "brick.h"

#include <QtCore/QSettings>

#include <QtCore/QDebug>

using namespace trikControl;

Brick::Brick()
{
	QSettings settings("./config.ini", QSettings::IniFormat);

	settings.beginGroup("Motor0");
	mMotor0.init(
			settings.value("ValueMin", 1500000).toInt()
			, settings.value("ValueMax", 1800000).toInt()
			, settings.value("DeviceFile", "/sys/class/pwm/ehrpwm.1:0/duty_ns").toString()
			);
	settings.endGroup();

	settings.beginGroup("Motor1");
	mMotor0.init(
			settings.value("ValueMin", 1500000).toInt()
			, settings.value("ValueMax", 1800000).toInt()
			, settings.value("DeviceFile", "/sys/class/pwm/ehrpwm.1:1/duty_ns").toString()
			);
	settings.endGroup();

	settings.beginGroup("Sensor0");
	mSensor0.init(
			settings.value("DeviceFile", "/sys/devices/platform/da850_trik/sensor_d1").toString()
			);
	settings.endGroup();

	settings.beginGroup("Sensor1");
	mSensor1.init(
			settings.value("DeviceFile", "/sys/devices/platform/da850_trik/sensor_d1").toString()
			);
	settings.endGroup();
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
