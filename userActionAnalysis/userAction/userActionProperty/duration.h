#pragma once

#include <QtCore/QObject>

class Duration : public QObject
{
	Q_OBJECT

public:
	Duration(int from = 0, int to = 0);
	~Duration();

	int from() const;
	int to() const;

	void setFrom(int from);
	void setTo(int to);

private:
	int mFrom; //ms
	int mTo; //ms
};
