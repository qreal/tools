#include "motor.h"

#include <QtCore/QDebug>

using namespace trikControl;

Motor::Motor()
{
}

void Motor::init(int powerMin, int powerMax, QString const& controlFile)
{
	mControlFile.setFileName(controlFile);
	mPowerMin = powerMin;
	mPowerMax = powerMax;
}


void Motor::setPower(int power)
{
	qDebug() << "Executing setPower command with power = " << power;

	if (!mControlFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered | QIODevice::Text)) {
		qDebug() << "Can't open motor control file " << mControlFile.fileName();
		return;
	}

	QString command;

	qreal const powerFactor = static_cast<qreal>(mPowerMax - mPowerMin) / 100;
	command.sprintf("%d\n", static_cast<int>(power * powerFactor + mPowerMin));
	mControlFile.write(command.toLatin1());
	mControlFile.close();
}

void Motor::powerOff()
{
	qDebug() << "Executing powerOff command";

	if (!mControlFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered | QIODevice::Text)) {
		qDebug() << "Can't open motor control file " << mControlFile.fileName();
		return;
	}

	mControlFile.write("0");
	mControlFile.close();
}
