#pragma once

#include "logEntry.h"

/// Parses the message of the given log entry and reproduces user`s action that logged there.
class EntryProcessor
{
public:
	explicit EntryProcessor(LogEntry const &entry);

	/// Starts parsing and reproducing of logged user action.
	void process();

private:
	void processMouseEntry();
	void processWheelEntry();
	void processKeyEntry();

	LogEntry const &mEntry;
};

