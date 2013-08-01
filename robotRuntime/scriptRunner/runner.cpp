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
	mRunnerThread = new QThread();
	mEngineWrapper = new ScriptEngineWrapper();
	connect(this, SIGNAL(threadRun(QString)), mEngineWrapper, SLOT(run(QString)));
	mEngineWrapper->moveToThread(mRunnerThread);
	mEngineWrapper->moveSubobjectsToThread(mRunnerThread);
	mRunnerThread->start();
}

void Runner::run(QString const &script)
{
	if (mEngineWrapper->isRunning()) {
		qDebug() << "Script is already running";

		return;
	}

	emit threadRun(script);
}

void Runner::abort()
{
	// TODO: wt* is this sh**?
	mRunnerThread->terminate();
	delete mRunnerThread;
	mRunnerThread = new QThread();

	delete mEngineWrapper;
	mEngineWrapper = new ScriptEngineWrapper();
	connect(this, SIGNAL(threadRun(QString)), mEngineWrapper, SLOT(run(QString)));
	mEngineWrapper->moveToThread(mRunnerThread);
	mEngineWrapper->moveSubobjectsToThread(mRunnerThread);

	mRunnerThread->start();
}
