#pragma once;
#include <link.h>
#include <figure.h>

class Field
{
public:
	Field();
	Field(QList < Component *> *components);
	~Field();
	QList < Figure *> *getFigures() const;
	QList < Link *> *getLinks() const;
	QList < Component *> *getComponents() const;
	static bool pointInContur(SquarePos & point, QList < Component *> *comps);
	static bool compInContur(Component *comp, QList < Component *> *comps);

private:
	QList < Figure *> *mFigures;
	QList < Link *> *mLinks;
	QList < Component *> *mComponents;  //list of all components
};
