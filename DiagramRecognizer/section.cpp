#pragma once;
#include <section.h>

Recognizer::Recognizer() { }
int Recognizer::getType(QList<Component *> *shell) { return 0; }

Section::Section()
{
	mComps = new QList < Component *>();
}
Section::Section(QList < Component *> *components)
{
	mComps = new QList < Component *>(*components);
}
QList < Component *> * Section::getComps() const
{
	return mComps;
}
