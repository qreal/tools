#pragma once;
#include <eItems.h>

Recognizer::Recognizer() { }
int Recognizer::getType(QList < Component *> *shell) { return 0; }

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

EFigure::EFigure()
{
	mShell = new QList < Component *>();
	mSections = new QList < Section *>();
	mId = 0;
}
EFigure::EFigure(QList < Component *> *shell)
{
	mShell = shell;
	mSections = new QList < Section *>();
	mId = 0;
}
EFigure::EFigure(QList < Component *> *shell, QList < Section *> *sections)
{
	mShell = shell;
	mSections = sections;
	mId= 0;
}
EFigure::EFigure(QList < Component *> *shell, QList < Section *> *sections, int id)
{
	mShell = shell;
	mSections = sections;
	mId = id;
}
EFigure::EFigure(QList < Component *> *shell, int id)
{
	mShell = shell;
	mSections = new QList < Section *>();
	mId = id;
}
void EFigure::addSection(QList < Component *> *comps)
{
	mSections->push_front(new Section(comps));
}
void EFigure::addSection(Section *section)
{
	mSections->push_front(section);
}
QList < Component *> *EFigure::getShell() const { return mShell; }
QList < Section *> *EFigure::getSections() const { return mSections; }

ELink::ELink()
{
	mComponent = new Component();
	mFigure1 = mFigure2 = 0;  //null
}
ELink::ELink(Component *component)
{
	mComponent = component;
	mFigure1 = mFigure2 = 0;  //null
}
ELink::ELink(Component *component, EFigure *figure1, EFigure *figure2)
{
	mComponent = component;
	mFigure1 = figure1;
	mFigure2 = figure2;
}
Component *ELink::getComponent() const { return mComponent; }
EFigure *ELink::getFigure1() const { return mFigure1; }
EFigure *ELink::getFigure2() const { return mFigure2; }

