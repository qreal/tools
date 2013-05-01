#pragma once;
#include "component.h"
#include <set>

class Recognizer  //doesn't exist here; somewhere else
{
public:
	Recognizer();
	static int getType(QList <Component *> *shell);
	static Component *reverse(Component *comp);
};

class Section
{
public:
	Section();
	Section(QList < Component *> *components);
	Section(Section *section);
	~Section();
	QList < Component *> *getComps() const;

private:
	QList < Component *> *mComps;
};
