#pragma once;
#include <graph.h>
#include <vector>
#include <stack>
#include <set>
#include <QDebug>

Graph::Graph()
{
	mMatrix = new IMatrix();
	mInterList = new InterList();
	mIList = new IList();
	mNodes = new std::set<SquarePos>();
	mEdges = new std::set<Component *>();
}
Graph::Graph(QList < Component *> *comps)
{
	initGraph(comps);
}
Graph::Graph(Graph &graph)
{
	mMatrix = new IMatrix(*(graph.getMatrix()));
	mInterList = new InterList(*(graph.getInterList()));
	mIList = new IList(*(graph.getIList()));
	mNodes = new std::set<SquarePos>(*(graph.getNodes()));
	mEdges = new std::set<Component *>(*graph.getEdges());
}
Graph::Graph(Graph &graph, int deep)
{
	if (deep == 0)
	{
		Graph(graph);
		return;
	}
	mNodes = new std::set<SquarePos>(*(graph.getNodes()));
	mEdges = new std::set<Component *>(*graph.getEdges());
	mInterList = new InterList();
	mIList = new IList();
	mMatrix = new IMatrix();
	for (std::set<Component *>::const_iterator i = mEdges->begin(); i != mEdges->end(); i++)
	{
		QList<Component *> *newList = new QList<Component *>(*(graph.getInterList(*i)));
		mInterList->insert(std::pair<Component *, QList<Component *> *>(*i, newList));
	}
	for (std::set<SquarePos>::const_iterator i = mNodes->begin(); i != mNodes->end(); i++)
	{
		std::set<Component *> *newList = new std::set<Component *>(*(graph.getIList(*i)));
		mIList->insert(std::pair<SquarePos, std::set<Component *> *>(*i, newList));
	}
}

Graph::Graph(Graph *graph)
{
	mMatrix = new IMatrix(*(graph->getMatrix()));
	mInterList = new InterList(*(graph->getInterList()));
	mIList = new IList(*(graph->getIList()));
	mNodes = new std::set<SquarePos>(*(graph->getNodes()));
	mEdges = new std::set<Component *>(*graph->getEdges());
}
Graph::~Graph()
{
	for (std::set<Component *>::const_iterator i = mEdges->begin(); i != mEdges->end(); i++)
	{
		delete mInterList->at(*i);
	}
	for (std::set<SquarePos>::const_iterator i = mNodes->begin(); i != mNodes->end(); i++)
	{
		delete mIList->at(*i);
	}
	delete mInterList;
	delete mIList;
	delete mNodes;
	delete mEdges;
	delete mMatrix;

}

/*QList < Component *> *Graph::depthSearch(Component *component)
{
	std::stack < Component *> *s = new std::stack < Component *>();
	QList < Component *> *res = new QList < Component *>();
	s->push(component);
	component->setIsFixed(true);
	while (!s->empty())
	{
			component = s->top();
		s->pop();
		for (QList < Component *>::iterator itr = mComps->begin(); itr != mComps->end(); itr++)
		{
			if ((*itr)->getIsFixed()) { continue; }
			if (intersects(component, *itr))
			{
				s->push(*itr);
				(*itr)->setIsFixed(true);
				res->push_front(*itr);
			}
		}
	}
	for (QList < Component *>::iterator itr = mComps->begin(); itr != mComps->end(); itr++)
	{
		(*itr)->setIsFixed(false);
	}
	delete s;
	return res;
}*/

QList < QList < Component *> *> *Graph::cSegmentation(QList < Component *> *comps, Graph &graph)  //splits all components into connected components
{
	std::stack<Component *> s;
	QList < QList < Component *> *> *res = new QList < QList < Component *> *>();
	QList < Component *> *copy = new QList < Component *> (*comps);
	Component *cur;
	std::set<Component *> marked;
	QList < Component *> *curList;
	while (!copy->empty())
	{
		curList = new QList < Component *>();
		s.push(copy->first());
		copy->removeFirst();
		curList->clear();
		//marked.clear();
		marked.insert(s.top());
		curList->push_back(s.top());
		while (!s.empty())
		{
			QList < Component *> *list = graph.getInterList(s.top());
			bool wereIn = false;
			for (QList < Component *>::iterator i = list->begin(); i != list->end(); i++)
			{
				if (marked.find(*i) != marked.end()) { continue; }
				wereIn = true;
				s.push(*i);
				curList->push_back(*i);
				int index = copy->indexOf(*i);
				copy->removeAt(index);
				marked.insert(*i);
			}
			if (!wereIn)
			{
				s.pop();
			}
		}
		res->push_back(curList);
	}
	delete copy;
	return res;
}

bool Graph::intersects(Component *comp1, Component *comp2) const
{
	return mMatrix->at(std::pair<Component *, Component *>(comp1, comp2));
}
IMatrix *Graph::getMatrix() const { return mMatrix; }
InterList *Graph::getInterList() const { return mInterList; }
QList < Component *> *Graph::getInterList(Component *component) const
{
	if (mInterList->find(component) == mInterList->end()) { return 0; }
	return mInterList->at(component);
}
std::set < Component * > *Graph::getIList(SquarePos const & node) const
{
	if (mIList->find(node) == mIList->end()) { return 0; }
	return mIList->at(node);
}
IList *Graph::getIList() const
{
	return mIList;
}
std::set < SquarePos > *Graph::getNodes() const
{
	return mNodes;
}
std::set < Component *> *Graph::getEdges() const
{
	return mEdges;
}
SquarePos Graph::intersectsAt(Component *comp1, Component *comp2) const
{
	if (!intersects(comp1, comp2)) { return SquarePos(-1, -1); }
	if (comp1->first() == comp2->first()) { return comp1->first(); }
	if (comp1->first() == comp2->last()) { return comp1->first(); }
	if (comp1->last() == comp2->first()) { return comp1->last(); }
	if (comp1->last() == comp2->last()) { return comp1->last(); }
}
void Graph::initGraph(QList < Component *> *comps)
{
	mIList = new IList();
	mInterList = new InterList();
	//mMatrix = new std::map<pair< Component *, Component * >, bool>();
	mMatrix = new IMatrix();
	mEdges = new std::set<Component *>();
	std::set < SquarePos > *nodes = new std::set < SquarePos >();
	for (QList < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		mEdges->insert(*i);
		QList < Component *> *curList = new QList < Component *>();
		for (QList < Component *>::iterator itr = comps->begin(); itr != comps->end(); itr++)
		{
			nodes->insert((*itr)->first());
			nodes->insert((*itr)->last());
			SquarePos point = Component::intersectsAt(*i, *itr);
			//if (Component::intersects(*i, *itr))
			if (point != SquarePos(-1, -1))
			{
				if (*itr != *i)
				{
					curList->push_front(*itr);
					//nodes->insert(point);
				}
				//std::pair p1 = std::pair<Component *, Component *>(*i, *itr);
				mMatrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(*i, *itr), true));
			}
			else
			{
				mMatrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(*i, *itr), false));
			}
		}
		mInterList->insert(std::pair<Component *, QList < Component *> *>(*i, curList));
	}
	mNodes = nodes;
	for (std::set<SquarePos>::iterator curNode = mNodes->begin(); curNode != mNodes->end(); curNode++)
	{
		std::set < Component *> *newList = new std::set < Component *>();
		for (QList < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
		{
			SquarePos begin = (*i)->first();
			SquarePos end = (*i)->last();
			if ((begin == *curNode) || (end == *curNode))
			{
				newList->insert(*i);
			}
		}
		mIList->insert(std::pair<SquarePos, std::set<Component *> * >(*curNode, newList));
	}
	/*for (IList::const_iterator i = mIList->begin(); i != mIList->end(); i++)
	{
		qDebug() << "Node: " << (*i).first.first << " " << (*i).first.second;
		std::set<Component *> *list = (*i).second;
		for (std::set < Component *>::const_iterator i = list->begin(); i != list->end(); i++)
		{
			qDebug() << (*i)->num;
		}
	}*/
}
bool Graph::mIListIsEmpty() const
{
	for (IList::const_iterator i = mIList->begin(); i != mIList->end(); i++)
	{
		std::set < Component * > *list = (*i).second;
		if (!list->empty()) { return false; }
	}
	return true;
}
bool Graph::mInterListIsEmpty() const
{
	for (InterList::const_iterator i = mInterList->begin(); i != mInterList->end(); i++)
	{
		QList < Component * > *list = (*i).second;
		if (!list->empty()) { return false; }
	}
	return true;
}
void Graph::eraseEdge(Component *edge)  //works only for the first graph type
{
	IMatrix *matrix = getMatrix();
	QList < Component *> *list = getInterList(edge);
	if (list == 0) { return; }
	mEdges->erase(edge);
	//mInterList->erase(std::pair<Component *, QList < Component *> *>(edge, list));
	mInterList->erase(edge);
	for (QList < Component *>::iterator i = list->begin(); i != list->end(); i++)
	{
		QList < Component *> *list2 = getInterList(*i);
		for (QList < Component *>::iterator itr = list2->begin(); itr != list2->end(); itr++)
		{
			if (*itr == edge)
			{
				list2->erase(itr);
				break;
			}
		}
	}
	for (QList < Component *>::iterator i = list->begin(); i != list->end(); i++)
	{
		/*matrix->erase(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(*i, edge), true));
		matrix->erase(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(edge, *i), true));
		matrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(edge, *i), false));
		matrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(*i, edge), false));*/
		matrix->erase(std::pair<Component *, Component *>(*i, edge));
		matrix->erase(std::pair<Component *, Component *>(edge, *i));
		matrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(edge, *i), false));
		matrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(*i, edge), false));
	}
	SquarePos beg = edge->first();
	SquarePos end = edge->last();
	std::set<Component *> *set = getIList(beg);
	set->erase(edge);
	set = getIList(end);
	set->erase(edge);
}
void Graph::operator =(Graph &graph)
{
	delete mIList;
	delete mInterList;
	delete mNodes;
	delete mEdges;
	delete mMatrix;
	mMatrix = new IMatrix(*(graph.getMatrix()));
	mInterList = new InterList(*(graph.getInterList()));
	mIList = new IList(*(graph.getIList()));
	mNodes = new std::set<SquarePos>(*(graph.getNodes()));
	mEdges = new std::set<Component *>(*graph.getEdges());
}

void Graph::insertEdge(Component *edge)
{
	InterList *intList = getInterList();
	QList < Component *> *newList = new QList < Component *>();
	mEdges->insert(edge);
	mNodes->insert(edge->first());
	mNodes->insert(edge->last());
	bool finish;
	for (std::set<Component *>::iterator i = mEdges->begin(); i != mEdges->end(); i++)
	{
		finish = false;
		Component *cur = *i;
		SquarePos pos = Component::intersectsAt(cur, edge);
		if (pos == SquarePos(-1, -1)) { finish = true; }
		mMatrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(edge, cur), !finish));
		mMatrix->insert(std::pair<std::pair<Component *, Component *>, bool>(std::pair<Component *, Component *>(cur, edge), !finish));
		if (finish) { continue; }
		if (cur == edge) { continue; }
		QList < Component *> *list = getInterList(cur);
		list->push_back(edge);
		newList->push_back(cur);
	}
	for (std::set<Component *>::iterator i = mEdges->begin(); i != mEdges->end(); i++)
	{
		SquarePos beg = edge->first();
		SquarePos end = edge->last();
		std::set<Component *> *sList = getIList(beg);
		if (sList == 0)
		{
			std::set<Component *> *newSet = new std::set<Component *>();
			newSet->insert(edge);
			mIList->insert(std::pair<SquarePos, std::set<Component *> *>(beg, newSet));
		}
		else
		{
			sList->insert(edge);
			//mIList->insert(std::pair<SquarePos, std::set<Component *> *>(beg, sList));
		}
		sList = getIList(end);
		if (sList == 0)
		{
			std::set<Component *> *newSet = new std::set<Component *>();
			newSet->insert(edge);
			mIList->insert(std::pair<SquarePos, std::set<Component *> *>(end, newSet));
		}
		else
		{
			sList->insert(edge);
			//mIList->insert(std::pair<SquarePos, std::set<Component *> *>(beg, sList));
		}
	}
	intList->insert(std::pair<Component *, QList < Component *> *>(edge, newList));
}
