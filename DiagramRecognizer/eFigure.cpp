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
	mShell = new QList < Component *>(*shell);
	mSections = new QList < Section *>();
	mId = 0;
}
EFigure::EFigure(QList < Component *> *shell, QList < Section *> *sections)
{
	mShell = new QList < Component *>(*shell);
	mSections = new QList < Section *>(*sections);
	mId= 0;
}
EFigure::EFigure(QList < Component *> *shell, QList < Section *> *sections, int id)
{
	mShell = new QList < Component *>(*shell);
	mSections = new QList < Section *>(*sections);
	mId = id;
}
EFigure::EFigure(QList < Component *> *shell, int id)
{
	mShell = new QList < Component *>(*shell);
	mSections = new QList < Section *>();
	mId = id;
}
EFigure::~EFigure()
{
	delete mShell;
	delete mSections;
}

void EFigure::addSection(QList < Component *> *comps)
{
	mSections->push_back(new Section(comps));
}
void EFigure::addSection(Section *section)
{
	mSections->push_back(section);
}
QList < Component *> *EFigure::getShell() const { return mShell; }
QList < Section *> *EFigure::getSections() const { return mSections; }
int EFigure::getId() const { return mId; }
