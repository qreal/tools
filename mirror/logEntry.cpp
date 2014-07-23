#include "logEntry.h"

#include <QtCore/QStringList>
#include <QtCore/QDateTime>

#include "defines.h"

LogEntry::LogEntry()
	: mLevel(fatal)
	, mTimestamp(0)
{
}

LogEntry::LogEntry(QString const &entry)
{
	QStringList const parts = entry.split(' ', QString::SkipEmptyParts);
	if (parts.count() < 5) {
		PRINT(QString("The log entry \"%1\" cannot be parsed.\n").arg(entry));
		return;
	}

	mLevel = stringToLevel(parts[0]);
	mTimestamp = QDateTime::fromString(parts[1], "yyyy-MM-ddThh:mm:ss.zzz").toMSecsSinceEpoch();
	// Next 3 parts are 'file @ line'.
	mMessage = QStringList(parts.mid(5)).join(' ');
}

LogEntry::Level LogEntry::level() const
{
	return mLevel;
}

qint64 LogEntry::timestamp() const
{
	return mTimestamp;
}

QString LogEntry::message() const
{
	return mMessage;
}

LogEntry::Level LogEntry::stringToLevel(QString const &level) const
{
	QString const preparedLevel = level.toUpper().trimmed();

	if (preparedLevel == "TRACE") {
		return trace;
	}

	if (preparedLevel == "DEBUG") {
		return debug;
	}

	if (preparedLevel == "INFO") {
		return info;
	}

	if (preparedLevel == "WARN") {
		return warning;
	}

	if (preparedLevel == "ERROR") {
		return error;
	}

	if (preparedLevel == "FATAL") {
		return fatal;
	}

	PRINT("Unknown logging level " + level + ". Falling back to TRACE.\n");
	return trace;
}
