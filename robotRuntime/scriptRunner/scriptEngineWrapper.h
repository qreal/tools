#pragma once

#include <QtCore/QString>
#include <QtCore/QThread>
#include <QtScript/QScriptEngine>

#include <trikControl/brick.h>

namespace scriptRunner
{

class ScriptEngineWrapper : public QObject
{
	Q_OBJECT

public:
	ScriptEngineWrapper();
	bool isRunning() const;
	void moveSubobjectsToThread(QThread * const thread);

public slots:
	/// Executes given script.
	void run(QString const &script);

private:
	QScriptEngine *mEngine;  // Has ownership.
	trikControl::Brick mBrick;
};

}
