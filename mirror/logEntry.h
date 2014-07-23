#pragma once

#include <QtCore/QString>

/// Represents one line in the log file
class LogEntry
{
public:
	/// Represents six logging levels supported by this tool.
	enum Level
	{
		trace = 0
		, debug
		, info
		, warning
		, error
		, fatal
	};

	/// Constructs invalid log entry
	LogEntry();

	explicit LogEntry(QString const &entry);

	/// Returns the debugging level of the entry.
	Level level() const;

	/// Returns timestamp of the entry (the number of milliseconds passed since epoch).
	qint64 timestamp() const;

	/// Returns the logging entry message itself.
	/// @warning The returned message may contain less whitespaces than the original one.
	QString message() const;

private:
	Level stringToLevel(QString const &level) const;

	Level mLevel;
	qint64 mTimestamp;
	QString mMessage;
};
