#pragma once;
#include <QList>
#include <component.h>

class CComponent  //connected component
{
public:
	CComponent();
	CComponent(QList < Component *> *components);
	~CComponent();
	int size() const;
	void removeAll(Component *component);
	QList < Component *> *getIntersectionList(Component *curComponent);
	QList < Component *> *getIntersectionList(QList < Component *> *comps);
	void addComponent(Component *newComponent);
	QList < Component *> *getComponents() const;
private:
	QList < Component *> *mComps;
};
