#include "worker.h"

#include <QtCore/QFileInfo>
#include <QtCore/QTimer>

#include "entryProcessor.h"

int const minimalEventsInterval = 10;
int const fastModeAcceleration = 5;

/// @todo: get rid of it somehow
int const timeToWaitForLoaded = 2000;

Worker::Worker(QString const &logPath, QString const &appPath, QStringList const &args, Speed speed)
	: mLog(logPath)
	, mStream(&mLog)
	, mApplicationPath(appPath)
	, mStartupArguments(args)
	, mSpeed(speed)
{
}

void Worker::go()
{
	if (!mLog.open(QFile::ReadOnly)) {
		PRINT(QString("Cannot open %1 for reading. Terminating.\n").arg(mLog.fileName()));
		return;
	}

	PRINT(QString("Starting %1...\n").arg(mApplicationPath));
	QProcess * const process = new QProcess(this);
	process->setWorkingDirectory(QFileInfo(mApplicationPath).absolutePath());
	process->start(mApplicationPath, mStartupArguments);
	if (!process->waitForStarted(5000)) {
		PRINT(QString("Cannot start %1. Terminating.\n").arg(mApplicationPath));
		return;
	}

	mCurrentLine = 0;
	mLastTimestamp = 0;
	readEntry();
}

void Worker::readEntry()
{
	if (mStream.atEnd()) {
		PRINT("Done.\n");
		return;
	}

	++mCurrentLine;
	mCurrentEntry = LogEntry(mStream.readLine());
	if (mCurrentEntry.timestamp() < mLastTimestamp) {
		PRINT(QString("Timestamp on the line %1 is invalid. Terminating.\n").arg(QString(mCurrentLine)));
		return;
	}

	qint64 const lastTimestamp =  mLastTimestamp
			? mLastTimestamp
			: mCurrentEntry.timestamp() - timeToWaitForLoaded;
	qint64 const toWait = speedUp(mCurrentEntry.timestamp() - lastTimestamp);
	mLastTimestamp = mCurrentEntry.timestamp();
	QTimer::singleShot(toWait, this, SLOT(invokeEntry()));
}

void Worker::invokeEntry()
{
	PRINT("Invoking " + mCurrentEntry.message() + "\n");
	EntryProcessor processor(mCurrentEntry);
	processor.process();
	readEntry();
}

int Worker::speedUp(int ms) const
{
	switch (mSpeed) {
	case original:
		return ms;
	case fast:
		return qMax(ms / fastModeAcceleration, minimalEventsInterval);
	case fastest:
		return qMin(ms, minimalEventsInterval);
	default:
		return ms;
	}
}
