#pragma once;
#include  <section.h>
#include <component.h>

class EFigure
{
public:
	EFigure();
	EFigure(QList < Component *> *shell);
	EFigure(QList < Component *> *shell, QList < Section *> *sections);
	EFigure(QList < Component *> *shell, QList < Section *> *sections, int id);
	EFigure(QList < Component *> *shell, int id);
	EFigure(EFigure *figure);
	~EFigure();
	void addSection(QList < Component *> *comps);
	void addSection(Section *section);
	QList < Component *> *getShell() const;
	QList < Section *> *getSections() const;
	int getId() const;

private:
	QList < Component *> *mShell;
	QList < Section *> *mSections;
	int mId;  //id in database
};
