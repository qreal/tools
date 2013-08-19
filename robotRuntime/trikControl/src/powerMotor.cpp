#include "powerMotor.h"

#include <QtCore/QDebug>

using namespace trikControl;

void PowerMotor::init(int engine)
{
	mEngine = engine;
}


void PowerMotor::setPower(int power)
{
	char command[100] = {0};

	sprintf(command, "i2cset -y 2 0x48 0x1%d 0x%x w", mEngine, power);

	qDebug() << QString(command);

	system(command);
}

void PowerMotor::powerOff()
{
	setPower(0);
}
