#pragma once;
#include "section.h"
#include "abstractRecognizer.h"
#include "recognizers/mixedGesturesManager.h"
#include "simpleFormsInitializer.h"

Recognizer::Recognizer() { }
int Recognizer::getType(QList<Component *> *shell)
{
	AbstractRecognizer *abstractRecognizer = new AbstractRecognizer(new MixedGesturesManager(),
												 SimpleFormsInitializer::initialForms());

	Component *newComp = new Component();
	foreach (Component *component, *shell)
	{
		newComp->append(*component);
	}
	if (abstractRecognizer->recognizeObject(newComp->figure(-1000, -1000)).empty())
	{
		delete newComp;
		return 0;
	}
	delete newComp;
	return 1;
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
