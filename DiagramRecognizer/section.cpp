#pragma once;
#include <section.h>

Recognizer::Recognizer() { }
int Recognizer::getType(QList<Component *> *shell)
{

}

Section::Section()
{
	mComps = new QList < Component *>();
}
Section::Section(QList < Component *> *components)
{
	mComps = new QList < Component *>(*components);
}
Section::~Section()
{
	delete mComps;
}
QList < Component *> * Section::getComps() const
{
	return mComps;
}
