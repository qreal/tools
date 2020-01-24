#include "component.h"
#include "stdlib.h"
#include "QDebug"

const int pointNum = 8;

int Component::mNextID = 0;

Component::Component()
{
	mDerivative1.first = 0;
	mDerivative1.second = 0;
	mDerivative2.first = 0;
	mDerivative2.second = 0;
	mHasSelfIntersection = false;
}

void Component::insertPos(const SquarePos &pos)
{
	for (int i = 0; i < this->size() - 1; i ++) {
		if (pos.distP1(at(i)) <= 1 && pos.distP1(at(i + 1)) <= 1) {
			insert(i + 1, pos);
			return;
		}
	}
	if  (empty() || pos.dist(back()) <= 1){
		push_back(pos);
		return;
	}
	if (pos.dist(at(0)) <= 1) {
		push_front(pos);
		return;
	}
	qDebug() << "could not insert " << pos.first << pos.second;
	foreach (SquarePos position, *this) {
		qDebug() << "inserted" << position.first << position.second;
	}
}

bool Component::isNeighbours(const SquarePos &pos1, const SquarePos &pos2) const
{
	return pos1.dist(pos2) <= 1;
}


void Component::analyze()
{
	if (at(0).dist(back()) <= neighbourhoodRad) {
		int i = 0;
		while (!mHasSelfIntersection && i < size()) {
			if (at(0).dist(at(i)) > neighbourhoodRad) {
				mHasSelfIntersection = true;
			}
			i ++;
		}
	}
	for (int i = 1; i <= std::min(pointNum, size() - 1); i++) {
		mDerivative1.first += at(i).first - at(0).first;
		mDerivative1.second += at(i).second - at(0).second;
		mDerivative2.first += at(size() - i - 1).first - back().first;
		mDerivative2.second += at(size() - i - 1).second - back().second;
	}
	if (size() > 1) {
		mDerivative1.first /= std::min(pointNum, size() - 1);
		mDerivative1.second /= std::min(pointNum, size() - 1);
		mDerivative2.first /= std::min(pointNum, size() - 1);
		mDerivative2.second /= std::min(pointNum, size() - 1);
	}
}

QPair<double, double> Component::derivativeBack()
{
	return mDerivative2;
}

QPair<double, double> Component::derivativeBegin()
{
	return mDerivative1;
}

void Component::insertDiagram(const Component &diagram, bool isBegin1, bool isBegin2)
{
	mHasSelfIntersection = mHasSelfIntersection && diagram.hasSelfIntersection();
	if (isBegin1 && !isBegin2) {
		for (int i = diagram.size() - 1; i >= 0; i --) {
			push_front(diagram.at(i));
		}
	}
	else if (!isBegin1 && isBegin2) {
		append(diagram);
	}
	else if (isBegin1 && isBegin2) {
		foreach (SquarePos const &pos, diagram) {
			push_front(pos);
		}
	}
	else {
		for (int i = diagram.size() - 1; i >= 0; i --) {
			push_back(diagram.at(i));
		}
	}
	analyze();
}


bool Component::hasSelfIntersection() const
{
	return mHasSelfIntersection;
}

PathVector Component::figure(int xMin, int yMin) const
{
	SquarePos previous(-10, -10);
	PointVector stroke;
	PathVector figure;
	foreach (SquarePos const &pos, *this)
	{
		if (!isNeighbours(previous, pos) && !stroke.isEmpty()) {
			figure.push_back(stroke);
			stroke.clear();
		}
		stroke.push_back(QPoint(pos.first * wStep + xMin,
								pos.second * hStep + yMin));
		previous = pos;
	}
	figure.push_back(stroke);
	return figure;
}

bool Component::isNegligible() const
{
	if (isEmpty()) {
		return true;
	}
	int minX = at(0).first;
	int maxX = at(0).first;
	int minY = at(0).second;
	int maxY = at(0).second;
	foreach (SquarePos const &pos, *this) {
		if (pos.first > maxX) {
			maxX = pos.first;
		}
		if (pos.first < minX) {
			minX = pos.first;
		}
		if (pos.second > maxY) {
			maxY = pos.second;
		}
		if (pos.second < minY) {
			minY = pos.second;
		}
		if (maxX - minX >= neighbourhoodRad || maxY - minY >= neighbourhoodRad) {
			return false;
		}
	}
	return true;
}

bool Component::intersects(Component *comp1, Component *comp2)
{
	Component::Iterator itr1, itr2;
	for (itr1 = comp1->begin(); itr1 != comp1->end(); itr1++)
	{
		for (itr2 = comp2->begin(); itr2 != comp2->end(); itr2++)
		{
			if (*itr1 == *itr2)
			{
				return true;
			}
		}
	}
	return false;
}
SquarePos Component::intersectsAt(Component *comp1, Component *comp2)
{
	SquarePos beg1 = comp1->first();
	SquarePos beg2 = comp2->first();
	SquarePos end1 = comp1->last();
	SquarePos end2 = comp2->last();
	if (beg1 == beg2) { return beg1; }
	if (beg1 == end2) { return beg1; }
	if (end1 == beg2) { return end1; }
	if (end1 == end2) { return end1; }
	return SquarePos(-1, -1);  //such point does't exist; no intersection
}
bool Component::getIsFixed() const { return isFixed; }
bool Component::setIsFixed(bool value) { isFixed = value; }
SquarePos Component::center() const
{
	SquarePos res(0, 0);
	int x = 0;
	int y = 0;
	int len = 0;
	for (Component::const_iterator i = this->begin(); i != this->end(); i++)
	{
		x += (*i).first;
		y += (*i).second;
		len++;
	}
	res.first= x / len;
	res.second = y / len;
	return res;
}
SquarePos Component::getAnotherSide(SquarePos const & point) const
{
	SquarePos begin = this->first();
	SquarePos end = this->last();
	if (begin == point) { return end; }
	else if (end == point) { return begin; }
	else { return SquarePos(-1, -1); }
}
bool Component::isClosed() const
{
	return first() == last();
}
SquarePos Component::center(QList < Component *> *comps)
{
	SquarePos res(0, 0);
	int x = 0;
	int y = 0;
	int len = 0;
	for (QList < Component *>::const_iterator itr = comps->begin(); itr != comps->end(); itr++)
	{
		for (Component::const_iterator i = (*itr)->begin(); i != (*itr)->end(); i++)
		{
			x += (*i).first;
			y += (*i).second;
			len++;
		}
	}
	res.first= x / len;
	res.second = y / len;
	return res;
}

QList < Component *>::iterator Component::getOuterComponent(QList < Component *> *comps)
{
	Component *cur;
	int minX, minY;
	int globMinX, globMinY;
	QList < Component *>::iterator res;
	globMinX = (*((*(comps->begin()))->begin())).first;
	globMinY = (*((*(comps->begin()))->begin())).second;
	for (QList < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		cur = *i;
		minX = (*(cur->begin())).first;
		minY = (*(cur->begin())).second;
		for (Component::const_iterator itr = cur->begin(); itr != cur->end(); itr++)
		{
			minX = (minX < (*itr).first) ? minX : (*itr).first;
			minY = (minY < (*itr).second) ? minY : (*itr).second;
		}
		if (minX < globMinX)
		{
			globMinX = minX;
			globMinY = minY;
			res = i;
		}
		else
		{
			if (minY < globMinY)
			{
				globMinX = minX;
				globMinY = minY;
				res = i;
			}
		}
	}
	return res;
}
QList < Component *> *Component::prioritetSort(QList < Component *> *comps)
{
	return new QList < Component *>();
}
