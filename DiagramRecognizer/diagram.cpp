#include "diagram.h"
#include "stdlib.h"
#include "QDebug"

const int pointNum = 8;

int Diagram::mNextID = 0;

Diagram::Diagram()
{
	mDerivative1.first = 0;
	mDerivative1.second = 0;
	mDerivative2.first = 0;
	mDerivative2.second = 0;
	mHasSelfIntersection = false;
	mID = mNextID;
	mNextID ++;
}

int Diagram::ID() const
{
	return mID;
}

//for connected diagrams
void Diagram::insertPos(const SquarePos &pos)
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
	qDebug() << "could not insert " << pos.first << pos.second << ID();
	foreach (SquarePos position, *this) {
		qDebug() << "inserted" << position.first << position.second;
	}
}

bool Diagram::isNeighbours(const SquarePos &pos1, const SquarePos &pos2) const
{
	return pos1.dist(pos2) <= 1;
}


void Diagram::analyze()
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

QPair<double, double> Diagram::derivativeBack()
{
	return mDerivative2;
}

QPair<double, double> Diagram::derivativeBegin()
{
	return mDerivative1;
}

void Diagram::insertDiagram(const Diagram &diagram, bool isBegin1, bool isBegin2)
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


bool Diagram::hasSelfIntersection() const
{
	return mHasSelfIntersection;
}

PathVector Diagram::figure(int xMin, int yMin) const
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

bool Diagram::isNegligible() const
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
