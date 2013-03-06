#pragma once;
#include <connectedComponent.h>

CComponent::CComponent()
{
	mComps = new QList < Component *> ();
}
CComponent::CComponent(QList < Component *> *components) : mComps(components) { }
CComponent::~CComponent()
{
	delete mComps;
}
int CComponent::size() const { return mComps->size(); }
void CComponent::removeAll(Component *component)
{
	mComps->removeAll(component);
}
QList < Component *> *CComponent::getIntersectionList(Component *curComponent)  //old version; better to delete
{
	QList < Component *> *result = new QList < Component *>();
	for (QList < Component *>::iterator itr = mComps->begin(); itr != mComps->end(); itr++)
	{
		if (Component::intersects(*itr, curComponent))
		{
			result->push_front(*itr);
		}
	}
	return result;
}
QList < Component *> *CComponent::getIntersectionList(QList < Component *> *comps)
{
}
/*QList < Component *> *getIntersectionList(Component *curComponent, Segmentator *segmentator)  //new version
{
QList < Component *> *result = new QList < Component *>(segmentator->mInterList[curComponent]);
	for (QList < Component *>::iteartor itr = result->begin(); itr != result->end(); itr++)
	{
		if (!comps->contains(*itr))
		{
			result->erase(itr);
		}
	}
	return res;
}*/
void CComponent::addComponent(Component *newComponent)
{
	mComps->push_front(newComponent);
}
QList < Component *> *CComponent::getComponents() const { return mComps; }
