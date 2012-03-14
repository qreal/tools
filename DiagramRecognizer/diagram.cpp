#include "diagram.h"
#include "stdlib.h"
#include "QDebug"

const int pointNum = 6;

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

int Diagram::mNextID = 0;

int Diagram::ID() const
{
  return mID;
}

//в предположении, что компонента всегда связна
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
  if (at(0).dist(back()) <= neighbourhoodRad)
	mHasSelfIntersection = true;
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
  qDebug() << "first position" << at(0).first << at(0).second
	  << "begin derivative" << mDerivative1.first << mDerivative1.second
	  << "last point" << back().first << back().second
	  << "back derivative" << mDerivative2.first << mDerivative2.second;
}

QPair<double, double> Diagram::getDerivativeBack()
{
  return mDerivative2;
}

QPair<double, double> Diagram::getDerivativeBegin()
{
  return mDerivative1;
}

void Diagram::insertDiagram(const Diagram &diagram, bool isBegin1, bool isBegin2)
{
  qDebug() << "try to insert";
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
	foreach (SquarePos pos, diagram) {
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
