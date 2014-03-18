#pragma once

#include <QtCore/QObject>

class LogParser : public QObject
{
	Q_OBJECT

public:
	LogParser();
	~LogParser();
};
