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
