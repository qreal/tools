#include "ruleElement.h"

QStringList const reserveRuleItems = (QStringList() << QString::fromUtf8("Начать группу {")
									  << QString::fromUtf8("} Завершить группу")
									  << QString::fromUtf8("или")
									  << QString::fromUtf8("Начать множество [")
									  << QString::fromUtf8("] Завершить множество"));

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

bool RuleElement::isRedTapeInstruction()
{
	return reserveRuleItems.contains(mContent);
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
