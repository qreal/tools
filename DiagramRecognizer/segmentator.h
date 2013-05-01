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
	void makeSegmentation();
	Graph *getGraph() const;
	QList < Component *> *getComponents() const;
	QList < EFigure *> *getFigures() const;
	QList < ELink *> *getLinks() const;
	static bool areConnected(std::set<Component *> *comps, Graph & graph);  //should be private
	static std::set<Component *> *extractBridge(std::set < Component *> *comps, Graph & graph);  //should be private
	class ESegmentator
	{
	public:
		ESegmentator();
		ESegmentator(QList<Component *> *cComp);
		~ESegmentator();
		void eSegmentation();
		void makeSectionSegmentation();
		void segmentateSection(EFigure *figure);  //should be private
		QList < Component *> *getCComp() const;
		QList < EFigure *> *getFigures() const;
		QList < ELink *> *getLinks() const;
		Graph *getGraph() const;
	private:
		QList < Component *> *mComps; //inner connected components
		QList < EFigure *> *mFigures;  //elementary figures
		QList < ELink *> *mLinks;  //elementary links
		Graph *mGraph;
		CComponent *filter(CComponent *comps);
		bool makeESegmentation(QList<Component *> *comps, QList<EFigure *> *&figures, QList<ELink *> *&links, Graph &graph);
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
	static QList<Component *> *getOuterShell(QList < Component *> *comps, Graph &graph);
	static QList < Component *> *getInnerShell(Component *comp, QList<Component *> *comps, Graph graph);
private:
	static void buildCycle(Component *comp, Graph & graph, QList<Component *> &newEdges);
	static void clearInnerEdges(QList < Component *> *edges, Graph & graph);
	static std::set<Component *> *QListToSet(QList < Component *> *comps);
	static QList < Component *> *SetToQList(std::set<Component *> *comps);
	static QList<Component *> *priorSort(QList<Component *> *comps);
	static QList < Component *> *priorSort(std::set<Component *> &set);
	//static Component *chooseLink(std::set<Component *> &comps, Graph &graph);
	QList < EFigure *> *mFigures;
	QList < ELink *> *mLinks;
	QList < Component *> *mComps;  //list of all components
	Graph *mGraph;
};
