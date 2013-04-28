#pragma once;
#include <segmentator.h>
#include <stack>
#include <field.h>
#include <iostream>

Segmentator::Segmentator()
{
	mComps = new QList < Component *>();
	mGraph = new Graph();
}
Segmentator::Segmentator(QList < Component *> *components)
{
	mComps = components;
	mGraph = new Graph(components);
}
Segmentator::~Segmentator()
{
	delete mComps;
	delete mGraph;
}
void Segmentator::makeSegmentation(QList < Figure *> *&figures, QList < Link *> *&links)
{
	ESegmentator *eSegmentator = new ESegmentator(mComps);
	eSegmentator->eSegmentation();
	//ASegmentator *aSegmentator = new ASegmentator(eSegmentator);
	//aSegmentator->aSegmentation();
	//figures = aSegmentator->getFigures();
	//links = aSegmentator->getLinks();
	delete eSegmentator;
	//delete aSegmentator;
}
QList < Component *> *Segmentator::getComponents() const
{
	return mComps;
}
Graph *Segmentator::getGraph() const
{
	return mGraph;
}
int Segmentator::dist(Component *comp, SquarePos point)
{
	int sum = 0;
	int dx, dy;
	for (Component::const_iterator i = comp->begin(); i != comp->end(); i++)
	{
		dx = (*i).first - point.first;
		dy = (*i).second - point.second;
		sum += dx*dx + dy*dy;
	}
	return sum;
}

/*QList < Component *> *Segmentator::getOuterShell(QList < Component *> *comps, Graph *graph)  //comps are connected
{
	std::set<Component *> *set1 = new std::set < Component *>();
	std::set<Component *> *set2 = new std::set < Component *>();
	for (QList < Component *>::const_iterator i = comps->begin(); i != comps->end(); i++)
	{
		set1->insert(*i);
	}
	QList < Component *> *res = new QList < Component *>();
	int maxDist = -1;
	int curDist;
	SquarePos center = Component::center(comps);
	QList < Component *> *curList;
	QList < Component *>::iterator resItr = res->begin();

	QList < Component *>::const_iterator beg = Component::getOuterComponent(comps);
	QList < Component *>::const_iterator itr = beg;
	SquarePos s1 = (*itr)->first();
	SquarePos s2 = (*itr)->last();
	res->push_front(*itr);
	set1->erase(*itr);
	maxDist = -1;
	curList = graph->getInterList(*itr);
	for (QList < Component *>::const_iterator i = curList->begin(); i != curList->end(); i++)
	{
		if (set1->find(*i) != set1->end())  //if found
		{
			curDist = Segmentator::dist(*i, center);
			if (curDist > maxDist)
			{
				maxDist = curDist;
				itr = i;
			}
		}
	}
	if (maxDist == -1)
	{
		return res;
	}
	res->push_front(*itr);
	set2->insert(*itr);
	resItr++;
	set1->erase(*itr);
	SquarePos tmp1 = (*itr)->first();
	SquarePos tmp2 = (*itr)->last();
	if ((s1 == tmp1) || (s1 == tmp2))
	{
		s1 = s2;
	}
	while (true)
	{
		maxDist = -1;
		curList = graph->getInterList(*itr);
		for (QList < Component *>::const_iterator i = curList->begin(); i != curList->end(); i++)
		{
			if (set1->find(*i) != set1->end())
			{
				curDist = Segmentator::dist(*i, center);
				if (curDist > maxDist)
				{
					maxDist = curDist;
					itr = i;
				}
			}
		}
		if (maxDist == -1)
		{
			for (QList < Component *>::const_iterator i = curList->begin(); i != curList->end(); i++)
			{
				if (set2->find(*i) != set2->end())
				{
					curDist = Segmentator::dist(*i, center);
					if (curDist > maxDist)
					{
						maxDist = curDist;
						itr = i;
					}
				}
			}
		}
		res->push_front(*itr);
		set2->insert(*itr);
		resItr++;
		set1->erase(*itr);
		SquarePos d1 = (*itr)->first();
		SquarePos d2 = (*itr)->last();
		if ((d1 == s1) || (d2 == s1))
		{
			break;
		}
		if (*beg == *itr) { break; }  //not needed; better delete
	}
	//res->erase(res->begin());
	return res;
}*/
bool Segmentator::areConnected(std::set <Component *> *comps, Graph & graph)
{
	std::stack<Component *> s;
	s.push(*(comps->begin()));
	std::set<Component *> marked;
	marked.insert(s.top());
	while (!s.empty())
	{
		bool wereInFor = false;
		QList < Component *> *list = graph.getInterList(s.top());
		for (QList < Component *>::iterator i = list->begin(); i != list->end(); i++)
		{
			if (wereInFor) { break; }
			Component *cur = *i;
			if (comps->find(cur) == comps->end()) { continue; }
			if (marked.find(cur) != marked.end()) { continue; }
			wereInFor = true;
			s.push(cur);
			marked.insert(cur);
		}
		if (!wereInFor)
		{
			s.pop();
		}
	}
	return comps->size() == marked.size();
}

std::set < Component *> *Segmentator::extractBridge(std::set < Component *> *comps, Graph &graph)
{
	std::set<Component *> *result = new std::set<Component *>();
	std::set<Component *> *copy = new std::set<Component *>(*comps);
	for (std::set < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		Component *cur = *i;
		copy->erase(cur);
		SquarePos beg = cur->first();
		SquarePos end = cur->last();
		std::set<Component *> *list1 = graph.getIList(beg);
		std::set<Component *> *list2 = graph.getIList(end);
		if (list1->size() == 1 || list2->size() == 1)
		{
			result->insert(cur);
			copy->insert(cur);
			continue;
		}
		if (!Segmentator::areConnected(copy, graph))
		{
			result->insert(cur);
		}
		copy->insert(cur);
	}
	delete copy;
	return result;
}

QList < Component *> *Segmentator::getOuterShell(QList < Component *> *components, Graph & graph)  //comps are connected
{
	std::set<Component *> *comps = new std::set<Component *>();
	for (QList < Component *>::iterator i = components->begin(); i != components->end(); i++)
	{
		comps->insert(*i);
	}
	for (std::set<Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		Component *curComp = *i;
		comps->erase(i);
		if (!Field::compInContur(curComp, comps))
		{
			comps->insert(curComp);
		}
	}
	QList < Component *> *compsList = new QList < Component *>();
	for (std::set < Component *>::const_iterator i = comps->begin(); i != comps->end(); i++)
	{
		compsList->push_back(*i);
	}
	delete comps;
	return compsList;
	/*std::stack<SquarePos> s;
	s.push((*(comps->begin()))->first());
	SquarePos start = s.top();
	std::set<Component *> markedEdges;
	QList < Component *> *result = new QList < Component *>();
	while(true)
	{
		bool wereInFor = false;
		std::set < Component *> *list = graph.getIList(s.top());
		for (std::set < Component *>::iterator i = list->begin(); i != list->end(); i++)
		{
			if (wereInFor) { break; }
			Component *curEdge = *i;
			if (markedEdges.find(curEdge) != markedEdges.end()) { continue; }
			if (comps->find(curEdge) == comps->end()) { continue; }
			wereInFor = true;
			SquarePos anotherSide = curEdge->getAnotherSide(s.top());
			s.push(anotherSide);
			result->push_back(curEdge);
			markedEdges.insert(curEdge);
			comps->erase(curEdge);
		}
		if (!wereInFor)
		{
			s.pop();
			result->push_back(result->last());
		}
		if (s.empty() || start == s.top()) { break; }
	}
	for (std::set<Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		result->push_back(*i);
	}
	delete comps;
	return result;*/
}
void Segmentator::clearInnerEdges(QList<Component *> *edges, Graph & graph)
{
	std::set < SquarePos> border;
	for (QList<Component *>::const_iterator i = edges->begin(); i != edges->end(); i++)
	{
		border.insert((*i)->first());
		border.insert((*i)->last());
	}
	IList *map = graph.getIList();
	for (IList::iterator i = map->begin(); i != map->end(); i++)
	{
		std::set < Component * > *list = (*i).second;
		for (std::set < Component * >::iterator itr = list->begin(); itr != list->end(); itr++)
		{
			if (Field::compInContur(*itr, edges))
			{
				list->erase(itr);
			}
		}
		SquarePos pos = (*i).first;
		map->erase(i);
		map->insert(std::pair<SquarePos, std::set<Component *> *>(pos, list));
	}
}

void Segmentator::buildCycle(Component *comp, Graph & graph, QList < Component *> &newEdges)
{
	newEdges.clear();
	std::stack<SquarePos> s;
	std::set<SquarePos> finalNodes;
	newEdges.push_back(comp);
	s.push(comp->first());
	finalNodes.insert(s.top());
	s.push(comp->last());
	finalNodes.insert(s.top());
	std::set<SquarePos> marked;
	bool finishWhile = false;
	while (!s.empty())
	{
		std::set<Component *> *list = graph.getIList(s.top());
		bool wereInFor = false;
		for (std::set<Component *>::iterator i = list->begin(); i != list->end(); i++)
		{
			if (wereInFor) { break; }
			Component *cur = *i;
			SquarePos anotherSide = cur->getAnotherSide(s.top());
			if (marked.find(anotherSide) != marked.end()) { continue; }
			wereInFor = true;
			s.push(anotherSide);
			marked.insert(anotherSide);
			newEdges.push_back(cur);
			if (finalNodes.find(anotherSide) != marked.end())  //was found
			{
				finishWhile = true;
				break;
			}
		}
		if (finishWhile) { break; }
		if (!wereInFor)
		{
			newEdges.removeLast();
			s.pop();
		}
	}
}

QList < Component *> *Segmentator::getInnerShell(Component *comp, QList < Component *> *comps, Graph &graph)  //comps are connected
{
	Graph cGraph(graph);
	std::set<Component *> *compsSet = Segmentator::QListToSet(comps);
	QList < Component *> cComps(*comps);
	QList < Component *> newEdges;
	QList < Component *> *edges = new QList < Component *>();
	std::set<SquarePos> finalNodes;
	QList < Component *> *res = new QList < Component *>();
	cGraph.eraseEdge(comp);
	while (true)
	{
		Segmentator::buildCycle(comp, cGraph, newEdges);
		if (newEdges.empty()) { break; }
		delete edges;
		edges = new QList<Component *>(newEdges);
		for (QList < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
		{
			if (!Field::compInContur(*i, compsSet))
			{
				cGraph.eraseEdge(*i);
				compsSet->erase(*i);
			}
		}
		for (QList < Component *>::iterator i = newEdges.begin(); i != newEdges.end(); i++)
		{
			cGraph.eraseEdge(*i);
		}
	}
	return edges;
}

QList<Component *> *Segmentator::priorSort(QList <Component *> *comps)
{
	return comps;
}

std::set<Component *> *Segmentator::QListToSet(QList < Component *> *comps)
{
	std::set<Component *> *set = new std::set<Component *>();
	for (QList < Component *>::const_iterator i = comps->begin(); i != comps->end(); i++)
	{
		set->insert(*i);
	}
	return set;
}
QList < Component *> *Segmentator::SetToQList(std::set<Component *> *comps)
{
	QList < Component *> *list = new QList < Component *>();
	for (std::set < Component *>::const_iterator i = comps->begin(); i != comps->end(); i++)
	{
		list->push_back(*i);
	}
	return list;
}

Segmentator::ASegmentator::ASegmentator()
{
	mFigures = new QList < Figure *>();
	mLinks = new QList < Link *>();
}
Segmentator::ASegmentator::ASegmentator(ESegmentator *eSegmentator) : eSegmentator(eSegmentator) { }
void Segmentator::ASegmentator::aSegmentation()
{

}
Segmentator::ESegmentator *Segmentator::ASegmentator::getESegmentator() const
{
	return eSegmentator;
}
QList < Figure *> *Segmentator::ASegmentator::getFigures() const
{
	return mFigures;
}

QList < Link *> *Segmentator::ASegmentator::getLinks() const
{
	return mLinks;
}
Segmentator::ESegmentator::ESegmentator()
{
	mComps = new QList<Component *>();
	mFigures = new QList < EFigure *>();
	mLinks = new std::set < ELink *>();
	mGraph = new Graph();
}
Segmentator::ESegmentator::ESegmentator(QList <Component *> *cComp)
{
	mComps = new QList < Component *>(*cComp);
	mFigures = new QList < EFigure *>();
	mLinks = new std::set < ELink *>();
	mGraph = new Graph(mComps);
}
void Segmentator::ESegmentator::eSegmentation()  //splits connected component into elementary items (figures and links)
{
	QList < EFigure *> figures;
	QList < ELink *> links;
	Graph graph = *mGraph;
	bool res = makeESegmentation(mComps, figures, links, graph);
	if (!res) { return; }			//if error accured
	makeSectionSegmentation();
}
void Segmentator::ESegmentator::makeSectionSegmentation()
{
	for (QList < EFigure *>::iterator itr = mFigures->begin(); itr != mFigures->end(); itr++)
	{
		QList < Component *> *edges = mComps; //link to Segmentator!!!(get it somehow)
		QList < Component *> *links = new QList < Component *>();
		for (std::set < ELink *>::iterator i = mLinks->begin(); i != mLinks->end(); i++)
		{
			links->push_front((*i)->getComponent());
		}
		for (QList < Component *>::iterator i = edges->begin(); i != edges->end(); i++)
		{
			if (((*i)->getIsFixed()) || (links->indexOf(*i)!=-1))  //if current edge doesn't belong to any figure or link
			{
				edges->erase(i);
			}
		}
		//at this moment edges contain all inner lines in current figure
		segmentateSections(*itr, edges);
		for (QList <  Component *>::iterator i = edges->begin(); i != edges->end(); i++)
		{
			(*i)->setIsFixed(true);
		}
		delete links;
		delete edges;
	}
}
//CComponent *getCComp() { return mCComp; }
QList < Component *> *Segmentator::ESegmentator::getCComp() const { return mComps; }
QList < EFigure *> *Segmentator::ESegmentator::getFigures() const { return mFigures; }
std::set < ELink *> *Segmentator::ESegmentator::getLinks() const { return mLinks; }
Graph *Segmentator::ESegmentator::getGraph() const { return mGraph; }

void Segmentator::ESegmentator::segmentateSections(EFigure *figure, QList < Component *> *innerComps)
{
	QList < Component *> *allComps = new QList < Component *>();
	for (QList < Component *>::iterator itr = figure->getShell()->begin(); itr != figure->getShell()->end(); itr++)
	{
		allComps->push_front(*itr);
	}
	for (QList < Component *>::iterator itr = innerComps->begin(); itr != innerComps->end(); itr++)
	{
		allComps->push_front(*itr);
	}
	QList < Component *> *shell = new QList < Component *>(*(figure->getShell()));
	while (allComps->size() != 0)
	{
		//the following line MUST NOT BE COMMENTED
		//QList < Component *> *inner = Segmentator::getInnerShell(allComps, mGraph);
		QList < Component *> *inner;
		figure->addSection(inner);
		for (QList < Component *>::iterator itr = inner->begin(); itr != inner->end(); itr++)
		{
			int pos = shell->indexOf(*itr);
			if (pos != -1)
			{
				shell->removeAt(pos);
				inner->erase(itr);
				allComps->removeOne(*itr);
			}
		}
		for (QList < Component *>::iterator itr = inner->begin(); itr != inner->end(); itr++)
		{
			shell->push_front(*itr);
		}
		delete inner;
	}
	//next follows deleting memory; check it
	delete shell;
	delete allComps;
}
CComponent *Segmentator::ESegmentator::filter(CComponent *comps)  //filters fixed components
	{
	CComponent *res = new CComponent();
	for (QList < Component *>::iterator itr = comps->getComponents()->begin(); itr != comps->getComponents()->end(); itr++)
	{
		if (!(*itr)->getIsFixed())
		{
			res->addComponent(*itr);
		}
	}
	delete comps;
	return res;
}
bool Segmentator::ESegmentator::makeESegmentation(QList < Component *> *comps, QList < EFigure *> &figures, QList < ELink *> &links, Graph &graph)  //comps are connected
{
	QList < EFigure *> newFigures;
	QList < ELink *> newLinks;
	QList < QList < Component *> *> *connComps = Graph::cSegmentation(comps, graph);
	if (connComps->size() > 0)
	{
		bool res;
		for (QList < QList < Component *> *>::const_iterator i = connComps->begin(); i != connComps->end(); i++)
		{
			Graph newGraph(*i);
			res = makeESegmentation(*i, newFigures, newLinks, newGraph);
			if (!res)
			{
				for (QList < QList < Component *> *>::const_iterator itr = connComps->begin(); itr != connComps->end(); itr++)
				{
					delete *itr;
				}
				delete connComps;
				return false;
			}
			figures += newFigures;
		}
		return true;
	}
	QList < Component *> *shell = Segmentator::getOuterShell(comps, graph);
	std::set<Component *> *shellSet = Segmentator::QListToSet(comps);
	int type = Recognizer::getType(shell);
	if (type != 0)
	{
		EFigure *newFigure = new EFigure(shell);
		figures.push_back(newFigure);
		return true;
	}
	std::set<Component *> potLinks;  //potential Links
	for (QList < Component *>::iterator i = shell->begin(); i != shell->end(); i++)
	{
		Component *cur = (*i);
		SquarePos beg = cur->first();
		SquarePos end = cur->last();
		std::set<Component *> *list = graph.getIList(beg);
		bool begOk = list->size() >= 2;
		list = graph.getIList(end);
		bool endOk = list->size() >= 2;
		if (begOk && endOk)
		{
			potLinks.insert(cur);
		}
	}
	std::set<Component *> *curLinks = Segmentator::extractBridge(shellSet, graph);
	delete shell;
	delete shellSet;
	for (std::set<Component *>::const_iterator i = curLinks->begin(); i != curLinks->end(); i++)
	{
		if (potLinks.find(*i) == potLinks.end())
		{
			//delete shell;
			//delete shellSet;
			return false;
		}
	}
	QList < Component *> *copyComps = new QList < Component *>(*comps);
	if (curLinks->size() > 0)
	{
		for (std::set<Component *>::iterator i = curLinks->begin(); i != curLinks->end(); i++)
		{
			Component *cur = *i;
			int index = copyComps->indexOf(cur);
			copyComps->removeAt(index);
			graph.eraseEdge(cur);
		}
		bool res = makeESegmentation(copyComps, newFigures, newLinks, graph);
		if (!res)
		{
			//delete shell;
			//delete shellSet;
			return false;
		}
		figures += newFigures;
		return true;
	}
	QList < Component *> *sComps = Segmentator::priorSort(comps);
	for (QList<Component *>::iterator i = sComps->begin(); i != sComps->end(); i++)
	{
		Component *cur = *i;
		int index = copyComps->indexOf(cur);
		copyComps->removeAt(index);
		Graph newGraph(graph);
		newGraph.eraseEdge(cur);
		bool res = makeESegmentation(copyComps, newFigures, newLinks, newGraph);
		if (res)
		{
			figures += newFigures;
			return true;
		}
	}
	return false;
}
