#pragma once

#include <QtScript/QScriptEngine>

#include <trikControl/brick.h>
#include <trikControl/motor.h>
#include <trikControl/sensor.h>

namespace scriptRunner
{

QScriptValue motorToScriptValue(QScriptEngine *engine, trikControl::Motor* const &in);
void motorFromScriptValue(QScriptValue const &object, trikControl::Motor* &out);

}
