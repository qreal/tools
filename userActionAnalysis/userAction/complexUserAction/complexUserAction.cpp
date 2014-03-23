#include "userAction/complexUserAction/complexUserAction.h"

ComplexUserAction::ComplexUserAction(const QString &name, QList<UserAction *> userActions)
	: UserAction(name)
	, mUserActions(userActions)
{

}

ComplexUserAction::~ComplexUserAction()
{

}

QList<UserAction *> ComplexUserAction::userActions()
{
	return mUserActions;
}

Duration *ComplexUserAction::duration() const
{
	int from = 0;
	int to = 0;
	for (UserAction *userAction: mUserActions) {
		from += userAction->duration()->from();
		to += userAction->duration()->to();
	}
	return new Duration(from, to);
}
