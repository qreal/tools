#pragma once;
#include <link.h>
#include <figure.h>
#include <set>

class Field
{
public:
	Field();
	Field(QList < Component *> *components);
	~Field();
	QList < EFigure *> *getFigures() const;
	QList < ELink *> *getLinks() const;
	QList < Component *> *getComponents() const;
	static bool pointInContur(SquarePos & point, QList < Component *> *comps);
	static bool compInContur(Component *comp, QList < Component *> *comps);
	static bool compInContur(Component *comp, std::set<Component *> *comps);

private:
	QList < EFigure *> *mFigures;
	QList < ELink *> *mLinks;
	QList < Component *> *mComponents;  //list of all components
};
