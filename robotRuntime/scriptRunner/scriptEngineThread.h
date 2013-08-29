#pragma once

#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtScript/QScriptEngine>

#include <trikControl/brick.h>

namespace scriptRunner {

/// Worker object to be run in a separate thread for Qt Script execution. QScriptEngine::abortEvaluation does not work,
/// because script engine refuses to call QCoreApplication::ProcessEvents on robot for unknown reason.
/// On desktop computer (running Ubuntu 13.04) there is no need for multithreading, abortEvaluation() works fine.
class ScriptEngineThread : public QObject
{
	Q_OBJECT

public:
	/// Constructor.
	ScriptEngineThread();

	/// Destructor.
	virtual ~ScriptEngineThread();

	/// Returns true, if script engine is initialized and running.
	bool isRunning() const;

public slots:
	/// Initializes script engine.
	void init();

	/// Executes prepared script.
	void run(QString const &script);

	/// Marks worker for deletion and stops worker thread.
	void deleteWorker();

private:
	QScriptEngine *mEngine;  // Has ownership.
	trikControl::Brick mBrick;
};

}
