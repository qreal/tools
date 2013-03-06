#pragma once;
#include <segmentator.h>

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
QList < Component *> *Segmentator::getOuterShell(QList < Component *> *comps)  //comps are connected
{
	/*  here follows some actions  */
}
QList < Component *> *Segmentator::getInnerShell(QList < Component *> *comps)  //comps are connected
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
		QList < Component *> *inner = Segmentator::getInnerShell(allComps);
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
	shell = new CComponent(Segmentator::getOuterShell(cComp->getComponents()));
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
