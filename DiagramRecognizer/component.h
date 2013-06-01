#pragma once
#include "geometricForms.h"
#include <QList>

//const double infDerivative = 1000;

class Component : public QList<SquarePos>
{
public:
	int num;
	Component();
	void insertPos(SquarePos const & pos);
	void analyze();
	QPair<double, double> derivativeBegin();
	QPair<double, double> derivativeBack();
	void insertDiagram(const Component &diagram,
					   bool isBegin1, bool isBegin2);
	bool hasSelfIntersection() const;
	PathVector figure(int xMin, int yMin) const;
	bool isNegligible() const;
	bool getIsFixed() const;
	bool setIsFixed(bool value);
	SquarePos center() const;  //finds center of the component
	SquarePos getAnotherSide(const SquarePos & point) const;  //returns another side of the component
	bool isClosed() const;
	//finds any outer component (for example, left-upper one)
	static QList < Component *>::iterator getOuterComponent(QList < Component *> *comps);
	//finds the center of the list of components
	static SquarePos center(QList < Component *> *comps);
	static QList < Component *> *prioritetSort(QList < Component *> *comps);
	static bool intersects(Component *comp1, Component *comp2);
	static SquarePos intersectsAt(Component *comp1, Component *comp2);

private:
	bool isFixed;
	bool isNeighbours(SquarePos const & pos1, SquarePos const & pos2) const;
	static int mNextID;
	bool mHasSelfIntersection;
	int mID;
	QPair<double,double> mDerivative1;
	QPair<double,double> mDerivative2;
};
