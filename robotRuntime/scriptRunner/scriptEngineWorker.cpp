#include "scriptEngineWorker.h"

#include "runner.h"

#include <QtCore/QDebug>

#include <trikControl/motor.h>
#include <trikControl/sensor.h>

#include "scriptableParts.h"

using namespace scriptRunner;
using namespace trikControl;

Q_DECLARE_METATYPE(Motor*)
Q_DECLARE_METATYPE(PowerMotor*)
Q_DECLARE_METATYPE(Sensor*)

ScriptEngineWorker::ScriptEngineWorker()
	: mEngine(NULL)
{
}

ScriptEngineWorker::~ScriptEngineWorker()
{
	delete mEngine;
}

void ScriptEngineWorker::init()
{
	qDebug() << "ScriptEngineWorker::init()";

	mEngine = new QScriptEngine(this);

	mEngine->setProcessEventsInterval(10);

	qScriptRegisterMetaType(mEngine, motorToScriptValue, motorFromScriptValue);
	qScriptRegisterMetaType(mEngine, sensorToScriptValue, sensorFromScriptValue);

	QScriptValue brickProxy = mEngine->newQObject(&mBrick);
	mEngine->globalObject().setProperty("brick", brickProxy);
}

void ScriptEngineWorker::run(QString const &script)
{
	qDebug() << "ScriptEngineWorker::run()";

	if (!mEngine) {
		qDebug() << "ScriptEngineWorker is not initialized";
	}

	if (mEngine->isEvaluating()) {
		qDebug() << "Script is already running";

		return;
	}

	QScriptValue const result = mEngine->evaluate(script);

	if (mEngine->hasUncaughtException()) {
		int line = mEngine->uncaughtExceptionLineNumber();

		qDebug() << "uncaught exception at line" << line << ":" << result.toString();
	}

	qDebug() << "ScriptEngineWorker::finished";

	thread()->quit();
}

void ScriptEngineWorker::deleteWorker()
{
	mEngine->abortEvaluation();
	deleteLater();
	thread()->quit();
}

bool ScriptEngineWorker::isRunning() const
{
	return mEngine && mEngine->isEvaluating();
}
