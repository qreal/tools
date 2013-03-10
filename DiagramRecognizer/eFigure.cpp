#pragma once;
#include <eFigure.h>

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
