#pragma once;
#include <eItems.h>
#include <connectedComponent.h>
#include <set>
#include <geometricForms.h>

typedef std::map < Component *, QList < Component *> *> InterList;
typedef std::map <std::pair< Component *, Component *>, bool> IMatrix;
typedef std::map <SquarePos, std::set < Component * > *> IList;

class Graph
{
public:
	Graph();
	Graph(QList < Component *> *comps);
	Graph(Graph & graph);  //copies
	Graph(Graph *graph);  //copies
	~Graph();
	//QList < Component *> *depthSearch(Component *component);
	//QList < CComponent *> *cSegmentation(QList < Component *> *comps);  //splits all components into connected components
	bool intersects(Component *comp1, Component *comp2) const;
	IMatrix *getMatrix() const ;
	InterList *getInterList() const;
	QList < Component *> *getInterList(Component *component) const;
	std::set < Component * > *getIList(SquarePos const & node) const;
	IList *getIList() const;
	std::set < SquarePos > *getNodes() const;
	SquarePos intersectsAt(Component *comp1, Component *comp2) const;
	bool mIListIsEmpty() const;
	bool mInterListIsEmpty() const;
	void eraseEdge(Component *edge);
	void insertEdge(Component *edge);  //not tested
	void operator =(Graph &graph);
	static QList < QList < Component *> *> *cSegmentation(QList<Component *> *comps, Graph &graph);
	std::set<Component *> *getEdges() const;


private:
	void initGraph(QList < Component *> *comps);
	IMatrix *mMatrix;
	InterList *mInterList;
	IList *mIList;
	std::set<Component *> *mEdges;
	std::set<SquarePos> *mNodes;

};
