#pragma once;
#include <figure.h>
#include <link.h>
#include <graph.h>
#include <connectedComponent.h>
#include <set>

class Segmentator
{
public:
	friend class ESegmentator;
	friend class ASegmentator;
	Segmentator();
	Segmentator(QList < Component *> *components);
	~Segmentator();
	void makeSegmentation(QList < Figure *> *&figures, QList < Link *> *&links);
	Graph *getGraph() const;
	QList < Component *> *getComponents() const;
	static bool areConnected(std::set<Component *> *comps, Graph & graph);  //should be private
	static std::set<Component *> *extractBridge(std::set < Component *> *comps, Graph & graph);  //should be private
	class ESegmentator
	{
	public:
		ESegmentator();
		ESegmentator(CComponent *cComp);
		void eSegmentation();
		void makeSectionSegmentation();
		QList < Component *> *getCComp() const;
		QList < EFigure *> *getFigures() const;
		std::set < ELink *> *getLinks() const;
		Graph *getGraph() const;
	private:
		CComponent *mCComp;  //inner connected component
		QList < EFigure *> *mFigures;  //elementary figures
		std::set < ELink *> *mLinks;  //elementary links
		Graph *mGraph;
		void segmentateSections(EFigure *figure, QList < Component *> *innerComps);
		CComponent *filter(CComponent *comps);
		bool makeESegmentation(CComponent *cComp);
	};
	class ASegmentator
	{
	public:
		ASegmentator();
		ASegmentator(ESegmentator *eSegmentator);
		void aSegmentation();
		ESegmentator *getESegmentator() const;
		QList < Figure *> *getFigures() const;
		QList < Link *> *getLinks() const;
	private:
		ESegmentator *eSegmentator;
		QList < Figure *> *mFigures;
		QList < Link *> *mLinks;
	};

private:
	static int dist(Component *comp, SquarePos point);
public:
	static std::set<Component *> *getOuterShell(QList < Component *> *comps, Graph &graph);
private:
	static void buildCycle(Graph & graph, std::set < SquarePos > & finalNodes, QList < Component *> *&newEdges);
	static void clearInnerEdges(QList < Component *> *edges, Graph & graph);
	static QList < Component *> *getInnerShell(QList < Component *> *comps, Graph *graph);
	QList < Component *> *mComps;  //list of all components
	Graph *mGraph;
};
