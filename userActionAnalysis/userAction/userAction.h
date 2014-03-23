#pragma once

#include <QtCore/QMap>
#include <QtCore/QStringList>

#include "userAction/userActionProperty/duration.h"

class UserAction : public QObject
{
	Q_OBJECT

public:
	UserAction(QString const &name);
	virtual ~UserAction();
	virtual QString userActionName() const;

	virtual void setRepeatCount(int const &repeatCount);
	virtual void setIsKeyAction(bool isKeyAction);
	virtual void setDuration(int from, int to);

	virtual int repeatCount() const;
	virtual bool isKeyAction() const;
	virtual Duration *duration() const;

private:
	QString mName;

	int mRepeatCount;
	bool mIsKeyAction;
	Duration *mDuration;
};
