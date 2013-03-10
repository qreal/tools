#pragma once;
#include <component.h>

class Recognizer  //doesn't exist here; somewhere else
{
public:
	Recognizer();
	static int getType(QList < Component *> *shell);
};

class Section
{
public:
	Section();
	Section(QList < Component *> *components);
	QList < Component *> *getComps() const;

private:
	QList < Component *> *mComps;
};
