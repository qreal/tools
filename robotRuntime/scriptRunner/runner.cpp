#include "runner.h"

#include <QtScript/QScriptEngine>

#include <QtCore/QDebug>

#include <trikControl/brick.h>
#include <trikControl/motor.h>
#include <trikControl/sensor.h>

#include "scriptableParts.h"

using namespace scriptRunner;
using namespace trikControl;

Q_DECLARE_METATYPE(Motor*)
Q_DECLARE_METATYPE(Sensor*)

void Runner::run(QString const &script)
{
	Brick brick;

	QScriptEngine engine;

	qScriptRegisterMetaType(&engine, motorToScriptValue, motorFromScriptValue);
	qScriptRegisterMetaType(&engine, sensorToScriptValue, sensorFromScriptValue);

	QScriptValue brickProxy = engine.newQObject(&brick);
	engine.globalObject().setProperty("brick", brickProxy);

	QScriptValue const result = engine.evaluate(script);

	if (engine.hasUncaughtException()) {
		int line = engine.uncaughtExceptionLineNumber();
		qDebug() << "uncaught exception at line" << line << ":" << result.toString();
	}
}
