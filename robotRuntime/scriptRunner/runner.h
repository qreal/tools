#pragma once

#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtCore/QThread>

#include "scriptEngineWrapper.h"

namespace scriptRunner
{

/// Executes scripts in Qt Scripting Engine.
class Runner : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	Runner();

	/// Executes given script.
	void run(QString const &script);

	/// Aborts script execution.
	void abort();

signals:
	void threadRun(QString const &script);

private:
	ScriptEngineWrapper *mEngineWrapper;  // Has ownership.
	QTimer mTestTimer;
	QThread *mRunnerThread;  // Has ownership.
};

}
