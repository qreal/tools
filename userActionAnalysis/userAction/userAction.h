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
	virtual void setDuration(int const &from, int const &to);

private:
	QString mName;

	int mRepeatCount;
	bool mIsKeyAction;
	Duration *mDuration;
};
