#pragma once

#include <QtCore/QString>

namespace scriptRunner
{

/// Executes scripts in Qt Scripting Engine.
class Runner
{
public:
	/// Executes given script.
	static void run(QString const &script);
};

}
