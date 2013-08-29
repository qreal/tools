#include "runner.h"

#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

#include <trikControl/motor.h>
#include <trikControl/sensor.h>

#include "scriptableParts.h"

using namespace scriptRunner;
using namespace trikControl;

Q_DECLARE_METATYPE(Motor*)
Q_DECLARE_METATYPE(Sensor*)

Runner::Runner()
	: mEngineWorker(NULL)
	, mRunnerThread(new QThread())
{
//	initWorkerObject();
//	mRunnerThread->start();
}

Runner::~Runner()
{
	emit threadDelete();

	// Restart thread to be able to process threadDelete signal.
	mRunnerThread->start();
	mRunnerThread->wait(100);
	mRunnerThread->deleteLater();
}

void Runner::run(QString const &script)
{
	qDebug() << "Runner::run";

	initWorkerObject();

	emit threadInit();
	emit threadRun(script);

	// Restart thread if needed (if it is already running, it will do nothing).
	mRunnerThread->start();
}

void Runner::runSynchronous(QString const &script)
{
	qDebug() << "Runner::runSynchronous()";

	initWorkerObject();

	emit threadInit();
	emit threadRun(script);

	// Block until thread is finished.
	mRunnerThread->start();
	mRunnerThread->wait();

	qDebug() << "Runner::runSynchronous() done";
}

void Runner::abort()
{
	qDebug() << "Runner::abort()";

	// If script engine does not want to return control, kill it completely and create new thread.
	mRunnerThread->quit();
	if (!mRunnerThread->wait(100)) {
		qDebug() << "Thread suspended, terminating";
		mRunnerThread->terminate();
		qDebug() << "Terminate called";
		mRunnerThread->wait();
		qDebug() << "Thread terminated";
	} else {
		qDebug() << "Exited gracefully";
	}

	initWorkerObject();

	mRunnerThread->start();
}

void Runner::initWorkerObject()
{
	qDebug() << "Runner::initWorkerObject()";

	mRunnerThread->disconnect();

	// Exterminatus.
	delete mRunnerThread;

	mRunnerThread = new QThread();

	disconnect();

	// There will be memleak, old ScriptEngineWorker will be lost forever.
	// We can not gracefully delete ScriptEngineWorker, because thread where it lives was terminated, leaving it in
	// inconsistent state, subsequent restart and call of destructor fails on assert inside JavaScript core.
	mEngineWorker = new ScriptEngineThread();

	mEngineWorker->moveToThread(mRunnerThread);

	connect(this, SIGNAL(threadInit()), mEngineWorker, SLOT(init()));
	connect(this, SIGNAL(threadRun(QString const &)), mEngineWorker, SLOT(run(QString const &)));
	connect(this, SIGNAL(threadDelete()), mEngineWorker, SLOT(deleteWorker()));

	emit threadInit();
}
