#include "userAction/userAction.h"


UserAction::UserAction(const QString &name)
	: mName(name)
{

}

UserAction::~UserAction()
{

}

QString UserAction::userActionName() const
{
	return mName;
}
