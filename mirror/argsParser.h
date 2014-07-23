#pragma once

#include <QtCore/QStringList>

#include "defines.h"

/// Processes command line arguments and returns data in convenient form.
class ArgsParser
{
public:
	explicit ArgsParser(QStringList const &args);

	/// Returns true if user specified '--help' option or incorrect arguments, false otherwise.
	bool helpMode() const;

	/// Returns the manual text.
	QString helpText() const;

	/// Returns an absolute or relative path to a log file that will be reproduced by this tool.
	QString logFilePath() const;

	/// Returns how fast user actions must be played.
	Speed speed() const;

	/// Returns an absolute or relative path to an application that will be used for reproducing by this tool.
	QString applicationPath() const;

	/// Returns a list of arguments that will be used to start target application.
	QStringList startupArgs() const;

private:
	bool parseArg(QString const &arg);
	Speed stringToSpeed(QString const &rawSpeed, bool &ok) const;

	bool mHelpMode;
	QString mLogPath;
	QString mApplicationPath;
	Speed mSpeed;
	QStringList mStartupArgs;
};
