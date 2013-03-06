#pragma once;
#include <map>
#include <QList>
#include <component.h>

typedef std::map < Component *, QList < Component *> *> InterList;
typedef std::map <std::pair< Component *, Component *>, bool> IMatrix;

class Recognizer  //doesn't exist here
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

class EFigure
{
public:
	EFigure();
	EFigure(QList < Component *> *shell);
	EFigure(QList < Component *> *shell, QList < Section *> *sections);
	EFigure(QList < Component *> *shell, QList < Section *> *sections, int id);
	EFigure(QList < Component *> *shell, int id);
	void addSection(QList < Component *> *comps);
	void addSection(Section *section);
	QList < Component *> *getShell() const;
	QList < Section *> *getSections() const;

private:
	QList < Component *> *mShell;
	QList < Section *> *mSections;
	int mId;  //id in database
};

class ELink
{
public:
	ELink();
	ELink(Component *component);
	ELink(Component *component, EFigure *figure1, EFigure *figure2);
	Component *getComponent() const;
	EFigure *getFigure1() const;
	EFigure *getFigure2() const;
private:
	Component *mComponent;
	EFigure *mFigure1, *mFigure2;
};

class Figure
{
	//QList< EItem *> *items;
};

class Link : public ELink
{

};
