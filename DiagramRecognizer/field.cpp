#pragma once;
#include <link.h>
#include <figure.h>
#include <field.h>
#include <segmentator.h>
#include <iostream>
Field::Field()
{
	mFigures = new QList < EFigure *>();
	mLinks = new QList < ELink *>();
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
	for (QList < EFigure *>::const_iterator i = mFigures->begin(); i != mFigures->end(); i++)
	{
		delete *i;
	}
	delete mFigures;
	for (QList < ELink *>::const_iterator i = mLinks->begin(); i != mLinks->end(); i++)
	{
		delete *i;
	}
	delete mLinks;
	delete mComponents;
}
bool Field::pointInContur(SquarePos & point, QList < Component *> *comps)
{
	if (comps->empty()) { return false; }
	std::set < SquarePos> border;
	SquarePos up = (*((*(comps->begin()))->begin()));  //any SquarePos; for instance the first one
	SquarePos down(up);
	SquarePos left(up);
	SquarePos right(up);
	for (QList < Component *>::const_iterator i = comps->begin(); i != comps->end(); i++)
	{
		for (QList < SquarePos >::const_iterator itr = (*i)->begin(); itr != (*i)->end(); itr++)
		{
			SquarePos curPoint(*itr);
			border.insert(curPoint);
			if (up.first > curPoint.first) { up = curPoint; }
			if (down.first < curPoint.first) { down = curPoint; }
			if (left.second > curPoint.second) { left = curPoint; }
			if (right.second < curPoint.second) { right = curPoint; }
		}
	}
	std::set < SquarePos > black;
	std::set < SquarePos > gray;
	gray.insert(point);
	if (border.find(point) != border.end()) { return true; }
	int delta[3] = { -1, 0, 1};
	while(!gray.empty())
	{
		SquarePos curPos = *(gray.begin());
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (i == 1 && j == 1) { continue; }
				SquarePos newPos(curPos.first + delta[i], curPos.second + delta[j]);
				if ((border.find(newPos) == border.end()) && (black.find(newPos) == black.end()))
				{
					if ((newPos.first <= up.first) || (newPos.first >= down.first) || (newPos.second <= left.second) || (newPos.second >= right.second))
					{
						return false;
					}
					gray.insert(newPos);
				}
			}
		}
		gray.erase(curPos);
		black.insert(curPos);
	}
	return true;
}
bool Field::compInContur(Component *comp, QList < Component *> *comps)
{
	SquarePos point(comp->at(comp->size() / 2));
	return Field::pointInContur(point, comps);
}

bool Field::compInContur(Component *comp, std::set<Component *> *comps)
{
	SquarePos point(comp->at(comp->size() / 2));
	QList < Component *> *compList = new QList < Component *>();
	for (std::set<Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		compList->push_back(*i);
	}
	bool res =  Field::pointInContur(point, compList);
	delete compList;
	return res;
}

QList < Component *> *Field::getComponents() const
{
	return mComponents;
}
QList < EFigure *> *Field::getFigures() const
{
	return mFigures;
}
QList<ELink *> *Field::getLinks() const
{
	return mLinks;
}
