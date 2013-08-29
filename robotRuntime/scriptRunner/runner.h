#pragma once

#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QThread>

#include "scriptEngineThread.h"

namespace scriptRunner {

/// Executes scripts in Qt Scripting Engine.
class Runner : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	Runner();

	/// Destructor.
	virtual ~Runner();

	/// Executes given script asynchronously, returns immediately.
	/// If the script is already running, does nothing.
	/// @param script Script in Qt Script language to be executed.
	void run(QString const &script);

	/// Executes given script, but does not return until it is finished.
	/// @param script Script in Qt Script language to be executed.
	void runSynchronous(QString const &script);

	/// Aborts script execution.
	void abort();

signals:
	/// Signal for script runner thread to init script engine.
	void threadInit();

	/// Signal for script runner thread to begin execution.
	void threadRun(QString const &script);

	/// Signal for script runner thread to delete itself when possible.
	void threadDelete();

private:
	void initWorkerObject();

	ScriptEngineThread *mEngineWorker;  // Has ownership.
	QTimer mTestTimer;
	QThread *mRunnerThread;  // Has ownership.
};

}
