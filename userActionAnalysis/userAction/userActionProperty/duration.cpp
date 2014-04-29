#include "userAction/userActionProperty/duration.h"

Duration::Duration(int from, int to, int exact)
	: mFrom(from)
	, mTo(to)
    , mExact (exact)
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

int Duration::exact() const
{
    return mExact;
}

void Duration::setFrom(int from)
{
	mFrom = from;
}

void Duration::setTo(int to)
{
    mTo = to;
}

void Duration::setExact(int exact)
{
    mExact = exact;
}
