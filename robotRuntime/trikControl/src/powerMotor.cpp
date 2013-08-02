#include "powerMotor.h"

#include <QtCore/QDebug>

using namespace trikControl;

void PowerMotor::init(int engine)
{
	mEngine = engine;
}


void PowerMotor::setPower(int power)
{
	int direction = 0;
	int actualPower = 0;
	char i2ccommand[90] =  "i2cset -y 2 0x48 0x0 0x";
	char* output = i2ccommand;
	char data[20];

	if (power < 0) {
		direction = 1;
		actualPower = - power;
	}

	else if (power > 0) {
		direction = 2;
		actualPower =  power;
	} else {
		direction = 0;
	}

	sprintf(data,"%x", (actualPower << 8 ) + ((mEngine + 1) << 2) + direction);
	strcat(output,data);
	strcat(output," w");
	system(output);

	char i2ccommand2[90] =  "i2cset -y 2 0x48 0x0 0x";
	char* output2 = i2ccommand2;
	char data2[20];

	sprintf(data2,"%x", (actualPower << 8 ) + ((mEngine) << 2) + direction);
	strcat(output2,data2);
	strcat(output2," w");
	system(output2);
}

void PowerMotor::powerOff()
{
	setPower(0);
/*
	qDebug() << "Executing powerOff command";

	if (!mControlFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Unbuffered | QIODevice::Text)) {
		qDebug() << "Can't open motor control file " << mControlFile.fileName();
		return;
	}

	mControlFile.write("0");
	mControlFile.close();
	*/
}
