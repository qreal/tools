#pragma once;
#include <link.h>
#include <figure.h>
#include <field.h>
#include <segmentator.h>

Field::Field()
{
	mFigures = new QList < Figure *>();
	mLinks = new QList < Link *>();
	mComponents = new QList < Component *>();
}
Field::Field(QList < Component *> *components)
{
	mComponents = new QList < Component *>(*components);
	Segmentator *segmentator = new Segmentator(mComponents);
	segmentator->makeSegmentation(mFigures, mLinks);
	delete segmentator;
}
Field::~Field()
{
	delete mFigures;
	delete mLinks;
	delete mComponents;
}
QList < Component *> *Field::getComponents() const
{
	return mComponents;
}
QList < Figure *> *Field::getFigures() const
{
	return mFigures;
}
QList < Link *> *Field::getLinks() const
{
	return mLinks;
}
