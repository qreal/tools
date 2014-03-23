#include "userAction/userActionProperty/duration.h"

Duration::Duration(int from, int to)
	: mFrom(from)
	, mTo(to)
{

}

Duration::~Duration()
{

}

int Duration::from() const
{
	return mFrom;
}

int Duration::to() const
{
	return mTo;
}

void Duration::setFrom(int from)
{
	mFrom = from;
}

void Duration::setTo(int to)
{
	mTo = to;
}
