#pragma once

#include <QtCore/QMap>
#include <QtCore/QStringList>

#include "userAction/baseUserAction/baseUserAction.h"

enum ActionStatus {
	good = 0
	, neutral = 1
	, bad = 2
};

class ComplexUserAction : public UserAction
{

public:
	ComplexUserAction(QString const &name, QList<UserAction *> userActions);
	~ComplexUserAction();
	QList<UserAction *> userActions();
	void setUserActionsStatus(QMap<QString, ActionStatus> const &status);
	void addUserActionStatus(QString const &actionName, ActionStatus status);
	virtual Duration *duration() const;
	QStringList toStringList() const;

private:
	QStringList actionsToStringList(QList<UserAction *> userActions) const;
	QList<UserAction *> mUserActions;
	QMap<QString, ActionStatus> mUserActionsStatus;
};
