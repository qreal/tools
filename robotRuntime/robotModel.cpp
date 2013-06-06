#include "robotModel.h"

#include <QtCore/QDebug>

using namespace robotRuntime;

void RobotModel::motorOn(QString const &port, int power)
{
    qDebug() << "motorOn, port: " << port << ", power: " << power;
}

void RobotModel::beep()
{
    qDebug() << "beep";
}
