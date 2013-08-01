#pragma once

#include <QtCore/QString>
#include <QtScript/QScriptEngine>

#include <trikControl/brick.h>

namespace scriptRunner
{

/// Executes scripts in Qt Scripting Engine.
class Runner
{
public:
	/// Constructor.
	Runner();

	/// Executes given script.
	void run(QString const &script);

	/// Aborts script execution.
	void abort();

private:
	QScriptEngine mEngine;
	trikControl::Brick mBrick;
};

}
