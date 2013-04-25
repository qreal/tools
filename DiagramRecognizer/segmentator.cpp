#pragma once;
#include <segmentator.h>
#include <stack>
#include <field.h>

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
	ESegmentator *eSegmentator = new ESegmentator(new CComponent(mComps));
	eSegmentator->eSegmentation();
	ASegmentator *aSegmentator = new ASegmentator(eSegmentator);
	aSegmentator->aSegmentation();
	figures = aSegmentator->getFigures();
	links = aSegmentator->getLinks();
	delete eSegmentator;
	delete aSegmentator;
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

QList < Component *> *Segmentator::getOuterShell(QList < Component *> *comps, Graph & graph)  //comps are connected
{
	std::set < SquarePos > finalNodes;
	std::set < SquarePos > finalEdges;
	QList < Component *> *resEdges = new QList < Component *>();
	QList < Component *> *newEdges;
	std::set < SquarePos > innerNodes;
	finalNodes.insert(comps->first()->first()); //added any point (node)
	while (!graph.mIListIsEmpty())
	{
		Segmentator::buildCycle(graph, finalNodes, newEdges);
		for (QList < Component *>::iterator i = newEdges->begin(); i != newEdges->end(); i++)
		{
			resEdges->push_back(*i);
		}
		Segmentator::clearInnerEdges(resEdges, graph);
	}
	return resEdges;
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

void Segmentator::buildCycle(Graph & graph, std::set < SquarePos > & finalNodes, QList < Component *> *&newEdges)
{
	std::stack<SquarePos> s;
	QList <Component *> *curEdges = new QList <Component *>();
	QList < SquarePos > *curNodes = new QList < SquarePos >();
	std::set<Component *> *markedEdges = new std::set<Component *>();
	//adding element to stack s
	for (std::set < SquarePos >::iterator i = finalNodes.begin(); i != finalNodes.end(); i++)
	{
		if (!((graph.getIList(*i))->empty()))
		{
			s.push(*i);
			break;
		}
	}
	//at this moment stack s is not empty
	bool wereIn = false;
	bool finishWhile = false;
	while (!s.empty())
	{
		std::set<Component *> *edges = graph.getIList(s.top());
		wereIn = false;
		for (std::set<Component *>::iterator i = edges->begin(); i != edges->end(); i++)
		{
			if (wereIn) { break; }
			if (markedEdges->find(*i) != markedEdges->end()) { continue; }
			wereIn = true;
			SquarePos anotherSide = (*i)->getAnotherSide(s.top());
			std::set<SquarePos>::iterator itr = finalNodes.find(anotherSide);
			if (!(itr == finalNodes.end()))
			{
				curEdges->push_front(*i);
				finishWhile = true;
				break;
			}
			s.push(anotherSide);
			curEdges->push_front(*i);
			curNodes->push_front(anotherSide);
			markedEdges->insert(*i);
		}
		if (finishWhile) { break; }
		if (!wereIn)
		{
			curEdges->push_front(*(curEdges->begin()));
			curNodes->push_front(s.top());
			s.pop();
		}
	}
	newEdges = curEdges;
	/*foreach (SquarePos node, curNodes)
	{
		finalNodes.insert(node);
	}*/
}

QList < Component *> *Segmentator::getInnerShell(QList < Component *> *comps, Graph *graph)  //comps are connected
{
	/*  here follows some actions  */
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
	mCComp = new CComponent();
	mFigures = new QList < EFigure *>();
	mLinks = new std::set < ELink *>();
	mGraph = new Graph();
}
Segmentator::ESegmentator::ESegmentator(CComponent *cComp)
{
	mCComp = cComp;
	mFigures = new QList < EFigure *>();
	mLinks = new std::set < ELink *>();
	mGraph = new Graph(cComp->getComponents());
}
void Segmentator::ESegmentator::eSegmentation()  //splits connected component into elementary items (figures and links)
{
	bool res = makeESegmentation(mCComp);
	if (!res) { return; }			//if error accured
	makeSectionSegmentation();
}
void Segmentator::ESegmentator::makeSectionSegmentation()
{
	for (QList < EFigure *>::iterator itr = mFigures->begin(); itr != mFigures->end(); itr++)
	{
		QList < Component *> *edges = mCComp->getComponents(); //link to Segmentator!!!(get it somehow)
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
QList < Component *> *Segmentator::ESegmentator::getCComp() const { return mCComp->getComponents(); }
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
		QList < Component *> *inner = Segmentator::getInnerShell(allComps, mGraph);
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
bool Segmentator::ESegmentator::makeESegmentation(CComponent *cComp)
{
	if (cComp->size() == 0) { return false; }
	CComponent *copyComp = new CComponent(*cComp);
	CComponent *shell;
	std::set < Component *> *links = new std::set < Component *>();
	//the followin line MUST NOT BE COMMENTED
	//shell = new CComponent(Segmentator::getOuterShell(cComp->getComponents(), mGraph));
	shell = filter(shell);
	int type = Recognizer::getType(shell->getComponents());  //trying to recognise figure
	if (type!=0)  //some elementary figure was recognized
	{
		QList < Component *>::iterator itr;
		for (itr = shell->getComponents()->begin(); itr != shell->getComponents()->end(); itr++)
		{
			(*itr)->setIsFixed(true);
		}
		EFigure *newFigure = new EFigure(shell->getComponents(), type);
		mFigures->push_front(newFigure);
		return true;
	}
	else  //figure was not recognized
	{
		int len = shell->size();
		for (int i = 0; i < len; i++)
		{
			for (int j = i + 1; j < len; j++)
			{
				if (shell->getComponents()->at(i) == shell->getComponents()->at(i))
				{
					links->insert((shell->getComponents())->at(i));
				}
			}
		}
		if (links->size() != 0)  //if we know that some component is a link
		{
			for (std::set <ELink *>::iterator mItr = mLinks->begin(); mItr != mLinks->end(); mItr++)
			{
				for (std::set <Component *>::iterator itr = links->begin(); itr != links->end(); itr++)
				{
					if (Component::areClosed((*mItr)->getComponent(), *itr))
					{
						return false;
					}
				}
			}
			std::set < Component *>::iterator itr;
			for (itr = links->begin(); itr != links->end(); itr++)
			{
				copyComp->removeAll(*itr);
			}
			for (std::set < Component *>::iterator i = links->begin(); i != links->end(); i++)
			{
				mLinks->insert(new ELink(*i));
			}
			//mLinks->insert(links->begin(), links->end());
			QList <CComponent *> *newCComps = mGraph->cSegmentation(copyComp->getComponents());
			bool boolRes;
			for (QList <CComponent *>::iterator itr = newCComps->begin(); itr != newCComps->end(); itr++)
			{
				boolRes = makeESegmentation(*itr);
				if (!boolRes) { break; }
			}
			if (!boolRes)
			{
				//deleting links from mLinks
				for (std::set < Component *>::iterator itr = links->begin(); itr != links->end(); itr++)
				{
					std::set < ELink *>::iterator del;
					for (del = mLinks->begin(); del != mLinks->end(); del++)
					{
						if ((*del)->getComponent() == *itr)
						{
							mLinks->erase(del);
							break;  //dangerous
						}
					}
					mLinks->erase(del);
				}
			}
			else
			{
				return true;
			}
		}
		else  //we should guess which component is a link
		{
			QList < Component *> *prLinks = Component::prioritetSort(shell->getComponents());
			bool res;
			for (QList < Component *>::iterator prItr = prLinks->begin(); prItr != prLinks->end(); prItr++)
			{
				Component *link = *prItr;
				bool boolTmp = false;
				//checking current link
				for (std::set < ELink *>::iterator itr = mLinks->begin(); itr != mLinks->end(); itr++)
				{
					if (Component::areClosed((*itr)->getComponent(), link))
					{
						boolTmp = true;
						break;
					}
				}
				if (boolTmp) { continue; }
				QList < Component *>::iterator itr;
				for (itr = copyComp->getComponents()->begin(); itr != copyComp->getComponents()->end(); itr++)
				{
					if (link == *itr)
					{
						copyComp->getComponents()->erase(itr);
						break;
					}
				}
				mLinks->insert(new ELink(link));
				res = makeESegmentation(copyComp);
				if (res) { break; }
				else
				{
					//mLinks->erase(mLinks->find(link));
					for (std::set < ELink *>::iterator itr = mLinks->begin(); itr != mLinks->end(); itr++)
					{
						if ((*itr)->getComponent() == link)
						{
							mLinks->erase(itr);
							break;  //dangerous
						}
					}
				}
			}
			return res;
		}
	}
}
