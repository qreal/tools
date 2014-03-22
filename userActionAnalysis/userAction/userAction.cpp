#include "userAction/userAction.h"

int const defaultRepeatCount = 1;
bool const defaultIsKeyAction = true;
int const defaultDuration = 0;

UserAction::UserAction(const QString &name)
	: mName(name)
	, mRepeatCount(defaultRepeatCount)
	, mIsKeyAction(defaultIsKeyAction)
	, mDuration(new Duration(defaultDuration, defaultDuration))
{

}

UserAction::~UserAction()
{
	delete mDuration;
}

QString UserAction::userActionName() const
{
	return mName;
}

void UserAction::setRepeatCount(const int &repeatCount)
{
	mRepeatCount = repeatCount;
}

void UserAction::setIsKeyAction(bool isKeyAction)
{
	mIsKeyAction = isKeyAction;
}

void UserAction::setDuration(const int &from, const int &to)
{
	mDuration->setFrom(from);
	mDuration->setTo(to);
}
