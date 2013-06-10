#include "motor.h"

#include <QtCore/QDebug>

using namespace trikControl;

void Motor::setPower(int const &power)
{
	qDebug() << "setPower: " << power;
}
