#include "ruleElement.h"

RuleElement::RuleElement()
{

}

RuleElement::RuleElement(const QString &content, const QList<RuleElement *> &list
		, int repeatCount
		, bool isKeyAction
		, Duration *duration)
		: mContent(content)
		, mList(list)
		, mRepeatCount(repeatCount)
		, mIsKeyAction(isKeyAction)
		, mDuration(new Duration(duration->from(), duration->to()))
{

}

RuleElement::~RuleElement()
{
	delete mDuration;
}

void RuleElement::setContent(const QString &content)
{
	mContent = content;
}

void RuleElement::setList(const QList<RuleElement *> &list)
{
	mList.clear();
	mList << list;
}

void RuleElement::addList(const QList<RuleElement *> &list)
{
	mList << list;
}

void RuleElement::addElementToList(RuleElement *element)
{
	RuleElement *newElement = new RuleElement(element->content(), element->list(), element->repeatCount()
			, element->isKeyAction(), element->duration());
	mList.append(newElement);
}

bool RuleElement::isBaseAction()
{
	return mList.isEmpty();
}

QList<RuleElement *> RuleElement::list() const
{
	return mList;
}

QString RuleElement::content() const
{
	return mContent;
}

int RuleElement::repeatCount() const
{
	return mRepeatCount;
}

bool RuleElement::isKeyAction() const
{
	return mIsKeyAction;
}

Duration *RuleElement::duration() const
{
	return mDuration;
}
