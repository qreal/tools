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

private:
	QList < Figure *> *mFigures;
	QList < Link *> *mLinks;
	QList < Component *> *mComponents;  //list of all components
};
