#include "scriptEngineThread.h"

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

ScriptEngineThread::ScriptEngineThread()
	: mEngine(NULL)
{
}

ScriptEngineThread::~ScriptEngineThread()
{
	delete mEngine;
}

void ScriptEngineThread::init()
{
	qDebug() << "ScriptEngineWorker::init()";

	mEngine = new QScriptEngine(this);

	// mEngine->setProcessEventsInterval(10);

	qScriptRegisterMetaType(mEngine, motorToScriptValue, motorFromScriptValue);
	qScriptRegisterMetaType(mEngine, powerMotorToScriptValue, powerMotorFromScriptValue);
	qScriptRegisterMetaType(mEngine, sensorToScriptValue, sensorFromScriptValue);

	QScriptValue brickProxy = mEngine->newQObject(&mBrick);
	mEngine->globalObject().setProperty("brick", brickProxy);
}

void ScriptEngineThread::run(QString const &script)
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

void ScriptEngineThread::deleteWorker()
{
	mEngine->abortEvaluation();
	deleteLater();
	thread()->quit();
}

bool ScriptEngineThread::isRunning() const
{
	return mEngine && mEngine->isEvaluating();
}
