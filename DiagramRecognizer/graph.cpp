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
}
Graph::Graph(QList < Component *> *comps)
{
	initGraph(comps);
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

QList < CComponent *> *Graph::cSegmentation(QList < Component *> *comps)  //splits all components into connected components
{
	std::set<Component *> *setComps = new std::set<Component *>();
	for (QList < Component *>::iterator itr = comps->begin(); itr != comps->end(); itr++)
	{
		setComps->insert(*itr);
	}
	QList < CComponent *> *cComps = new QList < CComponent *>();
	QList < Component *> *curCComp;
	QList < Component *> *curList;
	std::stack<Component *> st;
	while (!setComps->empty())
	{
		st.push(*(setComps->begin()));
		setComps->erase(setComps->begin());
		curCComp = new QList < Component *>();
		while (!st.empty())
		{
			Component *top = st.top();
			curList = getInterList(top);
			for (QList < Component *>::iterator itr = curList->begin(); itr != curList->end(); itr++)
			{
				std::set<Component *>::iterator element = setComps->find(*itr);
				if (element != setComps->end())
				{
					st.push(*element);
					setComps->erase(element);
				}
			}
			if (top == st.top())
			{
				curCComp->push_front(st.top());
				st.pop();
			}
		}
		cComps->push_front(new CComponent(curCComp));
	}
	return cComps;
}

bool Graph::intersects(Component *comp1, Component *comp2) const
{
	return mMatrix->at(std::pair<Component *, Component *>(comp1, comp2));
}
IMatrix *Graph::getMatrix() const { return mMatrix; }
InterList *Graph::getInterList() const { return mInterList; }
QList < Component *> *Graph::getInterList(Component *component) const
{
	return mInterList->at(component);
}
std::set < Component * > *Graph::getIList(SquarePos const & node) const
{
	return mIList->at(node);
}
std::set < SquarePos > *Graph::getNodes() const
{
	return mNodes;
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
	qDebug() << "init graph" << comps->count();
	mIList = new IList();
	mInterList = new InterList();
	//mMatrix = new std::map<pair< Component *, Component * >, bool>();
	mMatrix = new IMatrix();
	std::set < SquarePos > *nodes = new std::set < SquarePos >();
	for (QList < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		QList < Component *> *curList = new QList < Component *>();
		for (QList < Component *>::iterator itr = comps->begin(); itr != comps->end(); itr++)
		{
			SquarePos point = Component::intersectsAt(*i, *itr);
			//if (Component::intersects(*i, *itr))
			if (point != SquarePos(-1, -1))
			{
				if (*itr != *i)
				{
					curList->push_front(*itr);
					nodes->insert(point);
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
	for (IList::const_iterator i = mIList->begin(); i != mIList->end(); i++)
	{
		qDebug() << "Node: " << (*i).first.first << " " << (*i).first.second;
		std::set<Component *> *list = (*i).second;
		for (std::set < Component *>::const_iterator i = list->begin(); i != list->end(); i++)
		{
			qDebug() << (*i)->num;
		}
	}
	qDebug() << "finish init";
}
bool Graph::mIListIsEmpty() const
{
	//foreach (std::pair<SquarePos, std::set<Component *> * > item, iList)
	/*for (IList::const_iterator i = mIList->begin(); i != mIList->end(); i++)
	{
		if (!((*i)->second.empty())) { return false; }
	}
	*/	return true;
}
