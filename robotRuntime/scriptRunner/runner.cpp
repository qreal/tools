#include "runner.h"

#include <QtCore/QDebug>

#include <trikControl/motor.h>
#include <trikControl/sensor.h>

#include "scriptableParts.h"

using namespace scriptRunner;
using namespace trikControl;

Q_DECLARE_METATYPE(Motor*)
Q_DECLARE_METATYPE(Sensor*)

Runner::Runner()
{
	mEngine.setProcessEventsInterval(100);

	qScriptRegisterMetaType(&mEngine, motorToScriptValue, motorFromScriptValue);
	qScriptRegisterMetaType(&mEngine, sensorToScriptValue, sensorFromScriptValue);

	QScriptValue brickProxy = mEngine.newQObject(&mBrick);
	mEngine.globalObject().setProperty("brick", brickProxy);
}


void Runner::run(QString const &script)
{
	if (mEngine.isEvaluating()) {
		qDebug() << "Script is already running";

		return;
	}

	QScriptValue const result = mEngine.evaluate(script);

	if (mEngine.hasUncaughtException()) {
		int line = mEngine.uncaughtExceptionLineNumber();

		qDebug() << "uncaught exception at line" << line << ":" << result.toString();
	}
}

void Runner::abort()
{
	if (mEngine.isEvaluating()) {
		mEngine.abortEvaluation();
	}
}
