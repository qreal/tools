#pragma once

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QProcess>

#include "defines.h"
#include "logEntry.h"

/// Performs user action mirroring: starts the application, parses the given log file
/// and reprodises user actions in fast mode via OS API.
class Worker : public QObject
{
	Q_OBJECT

public:
	Worker(QString const &logPath, QString const &appPath, QStringList const &args, Speed speed);

public slots:
	/// Starts the reproducing process.
	void go();

private slots:
	void readEntry();
	void invokeEntry();

private:
	int speedUp(int ms) const;

	QFile mLog;
	QTextStream mStream;
	QString const mApplicationPath;
	QStringList const mStartupArguments;
	Speed mSpeed;

	int mCurrentLine;
	LogEntry mCurrentEntry;
	qint64 mLastTimestamp;
};
