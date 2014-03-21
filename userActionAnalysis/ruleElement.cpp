#include "ruleElement.h"

RuleElement::RuleElement()
{

}

RuleElement::RuleElement(const QString &content, const QList<RuleElement *> &list)
		: mContent(content)
		, mList(list)
{

}

RuleElement::~RuleElement()
{

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

void RuleElement::addElementToList(const RuleElement &element)
{
	RuleElement *newElement = new RuleElement();
	newElement->setContent(element.content());
	newElement->setList(element.list());
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
