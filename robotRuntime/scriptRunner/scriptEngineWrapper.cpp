#include "scriptEngineWrapper.h"

#include "runner.h"

#include <QtCore/QDebug>

#include <trikControl/motor.h>
#include <trikControl/sensor.h>

#include "scriptableParts.h"

using namespace scriptRunner;
using namespace trikControl;

Q_DECLARE_METATYPE(Motor*)
Q_DECLARE_METATYPE(Sensor*)

ScriptEngineWrapper::ScriptEngineWrapper()
	: mEngine(NULL)
{
	mEngine = new QScriptEngine(this);

	mEngine->setProcessEventsInterval(10);

	qScriptRegisterMetaType(mEngine, motorToScriptValue, motorFromScriptValue);
	qScriptRegisterMetaType(mEngine, sensorToScriptValue, sensorFromScriptValue);

	QScriptValue brickProxy = mEngine->newQObject(&mBrick);
	mEngine->globalObject().setProperty("brick", brickProxy);
}

void ScriptEngineWrapper::moveSubobjectsToThread(QThread * const thread)
{
	mEngine->moveToThread(thread);
}

void ScriptEngineWrapper::run(QString const &script)
{
	if (mEngine->isEvaluating()) {
		qDebug() << "Script is already running";

		return;
	}

	QScriptValue const result = mEngine->evaluate(script);

	if (mEngine->hasUncaughtException()) {
		int line = mEngine->uncaughtExceptionLineNumber();

		qDebug() << "uncaught exception at line" << line << ":" << result.toString();
	}
}

bool ScriptEngineWrapper::isRunning() const
{
	return mEngine->isEvaluating();
}
