#pragma once;
#include <graph.h>
#include <vector>

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
	int len = comps->size();
	std::vector<bool> marked;
	marked.assign(len, false);
	QList < CComponent *> *cSegments = new QList <CComponent *>();  //list of connected components
	CComponent *cComp;  //current connected component
	for (int i = 0; i < len; i++)
	{
		if (!marked[i])
		{
			cComp = new CComponent();
			for (int j = i; j < len; j++)
			{
				if (!marked[j])
				{
					if (intersects(comps->at(i), comps->at(j)))
					{
						marked[j] = true;
						cComp->addComponent(comps->at(j));  //change: was mComps->at(j)
					}
				}
			}
			cSegments->push_back(cComp);  //adds current connected component to the std::set
		}
		marked[i] = true;
	}
	return cSegments;
}
bool Graph::intersects(Component *comp1, Component *comp2) const
{
	return mMatrix->at(std::pair<Component *, Component *>(comp1, comp2));
}
IMatrix *Graph::getMatrix() const { return mMatrix; }
InterList *Graph::getInterList() const { return mInterList; }
void Graph::initGraph(QList < Component *> *comps)
{
	mInterList = new InterList();
	//mMatrix = new std::map<pair< Component *, Component * >, bool>();
	mMatrix = new IMatrix();
	for (QList < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
	{
		QList < Component *> *curList = new QList < Component *>();
		for (QList < Component *>::iterator itr = comps->begin(); itr != comps->end(); itr++)
		{
			if (Component::intersects(*i, *itr))
			{
				if (*itr != *i)
				{
					curList->push_front(*itr);
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
}
