#include "scriptableParts.h"

#include <QtCore/QMetaType>

using namespace scriptRunner;
using namespace trikControl;

QScriptValue scriptRunner::motorToScriptValue(QScriptEngine *engine, Motor* const &in)
{
	return engine->newQObject(in);
}

void scriptRunner::motorFromScriptValue(QScriptValue const &object, Motor* &out)
{
	out = qobject_cast<Motor*>(object.toQObject());
}

QScriptValue scriptRunner::sensorToScriptValue(QScriptEngine *engine, trikControl::Sensor* const &in)
{
	return engine->newQObject(in);
}

void scriptRunner::sensorFromScriptValue(QScriptValue const &object, trikControl::Sensor* &out)
{
	out = qobject_cast<Sensor*>(object.toQObject());
}
