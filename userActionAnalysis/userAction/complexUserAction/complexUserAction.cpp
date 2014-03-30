#include "userAction/complexUserAction/complexUserAction.h"

ComplexUserAction::ComplexUserAction(const QString &name, QList<UserAction *> userActions)
	: UserAction(name)
	, mUserActions(userActions)
{
	mUserActionsStatus.clear();
}

ComplexUserAction::~ComplexUserAction()
{

}

QList<UserAction *> ComplexUserAction::userActions()
{
	return mUserActions;
}

void ComplexUserAction::setUserActionsStatus(const QMap<QString, ActionStatus> &status)
{
	mUserActionsStatus.clear();
	QMap<QString, ActionStatus>::const_iterator i = status.constBegin();
	while (i != status.constEnd()) {
		mUserActionsStatus.insert(i.key(), i.value());
		++i;
	}
}

void ComplexUserAction::addUserActionStatus(const QString &actionName, ActionStatus status)
{
	mUserActionsStatus.insert(actionName, status);
}

Duration *ComplexUserAction::duration() const
{
	int from = 0;
	int to = 0;
	for (UserAction *userAction: mUserActions) {
		if (userAction->isKeyAction() && isKeyAction()) {
			from += userAction->duration()->from();
		}
		to += userAction->duration()->to() * userAction->repeatCount();
	}
	return new Duration(from, to);
}

QStringList ComplexUserAction::toStringList() const
{
	return actionsToStringList(mUserActions);
}

QStringList ComplexUserAction::actionsToStringList(QList<UserAction *> userActions) const
{
	QStringList result;
	for (UserAction *userAction: userActions) {
		BaseUserAction *baseUserAction = dynamic_cast<BaseUserAction *>(userAction);
		if (baseUserAction != nullptr) {
			result << baseUserAction->actionToString();
		}
		else {
			ComplexUserAction *complexUserAction = dynamic_cast<ComplexUserAction *>(userAction);
			if (complexUserAction) {
				result << actionsToStringList(complexUserAction->userActions());
			}
		}
	}
	return result;
}
