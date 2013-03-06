#pragma once;
#include <eItems.h>
#include <connectedComponent.h>

class Graph
{
public:
	Graph();
	Graph(QList < Component *> *comps);
	//QList < Component *> *depthSearch(Component *component);
	QList < CComponent *> *cSegmentation(QList < Component *> *comps);  //splits all components into connected components
	bool intersects(Component *comp1, Component *comp2) const;
	IMatrix *getMatrix() const ;
	InterList *getInterList() const;

private:
	void initGraph(QList < Component *> *comps);
	IMatrix *mMatrix;
	InterList *mInterList;
};
