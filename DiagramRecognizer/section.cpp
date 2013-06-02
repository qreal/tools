#pragma once;
#include "section.h"
#include "abstractRecognizer.h"
#include "recognizers/mixedGesturesManager.h"
#include "simpleFormsInitializer.h"
#include "graph.h"

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
	/*std::set<SquarePos> sPos;
	std::set<SquarePos> finish;
	int count = 0;
	for (QList < Component *>::const_iterator i = shell->begin(); i != shell->end(); i++)
	{
		Component *cur = *i;
		SquarePos first = cur->first();
		SquarePos last = cur->last();
		if ((finish.find(first) != finish.end()) || (finish.find(last) != finish.end()))
		{
			return false;
		}
		if (sPos.find(first) != sPos.end())
		{
			finish.insert(first);
			count++;
		}
		if (sPos.find(last) != sPos.end())
		{
			finish.insert(last);
			count++;
		}
		if (first == last)
		{
			count++;
		}
		sPos.insert(first);
		sPos.insert(last);
	}
	if (shell->size() != count) { return false; }
	sPos.clear();
	for (QList < Component *>::const_iterator i = shell->begin(); i != shell->end(); i++)
	{
		foreach(SquarePos pos, *(*i))
		{
			sPos.insert(pos);
		}
	}
	SquarePos minUpper(*(sPos.begin()));
	for (std::set<SquarePos>::iterator i = sPos.begin(); i != sPos.end(); i++)
	{
		if (*i < minUpper) { minUpper = *i; }
	}
	SquarePos cur = minUpper;
	SquarePos delta[4] = {SquarePos(0, 1), SquarePos(1, 0), SquarePos(0, -1), SquarePos(-1, 0) };
	bool was = false;
	count = 0;
	SquarePos start = cur;
		for (int i = 0; i < 4; i++)
		{
			was = false;
			while (sPos.find(cur + delta[i]) != sPos.end())
			{
				//if (start == cur) { break; }
				cur = cur + delta[i];
				was = true;
				if ((cur == start) && (count == 3)) { return true; }
				if (cur == start) { return false; }
			}
			if (!was) { return false; }
			count++;
		}
	return false;*/
}
Component *Recognizer::reverse(Component *comp)
{
	Component *res = new Component();
	for (int i = 0; i < comp->size(); i++)
	{
		res->push_back(comp->last());
		comp->removeLast();
	}
	delete comp;
	return res;
}

Section::Section()
{
	mComps = new QList < Component *>();
	mType = 0;
}
Section::Section(QList < Component *> *components)
{
	mComps = new QList < Component *>(*components);
	setType(Recognizer::getType(components));
}
Section::Section(Section *section)
{
	mComps = new QList < Component *>(*section->getComps());
	mType = section->getType();
}
Section::~Section()
{
	delete mComps;
}
QList < Component *> * Section::getComps() const
{
	return mComps;
}
int Section::getType() const
{
	return mType;
}
void Section::setType(int value)
{
	mType = value;
}
