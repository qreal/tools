#pragma once
#include <cstdlib>
#include <stack>
#include <set>
#include <map>
#include <component.h>
#include <vector>

typedef std::map < Component *, QList < Component *> *> InterList;
typedef std::map <std::pair< Component *, Component *>, bool> IMatrix;

class EItem
{

};

class Recognizer  //doesn't exist here
{
public:
	Recognizer() { }
	static int getType(QList < Component *> *shell) { return 0; }
};

class Section
{
public:
	Section()
	{
		mComps = new QList < Component *>();
	}
	Section(QList < Component *> *components)
	{
		mComps = new QList < Component *>(*components);
	}
private:
	QList < Component *> *mComps;
};

class EFigure : public EItem
{
public:
	EFigure()
	{
		mShell = new QList < Component *>();
		mSections = new QList < Section *>();
		mId = 0;
	}
	EFigure(QList < Component *> *shell)
	{
		mShell = shell;
		mSections = new QList < Section *>();
		mId = 0;
	}
	EFigure(QList < Component *> *shell, QList < Section *> *sections)
	{
		mShell = shell;
		mSections = sections;
		mId= 0;
	}
	EFigure(QList < Component *> *shell, QList < Section *> *sections, int id)
	{
		mShell = shell;
		mSections = sections;
		mId = id;
	}
	EFigure(QList < Component *> *shell, int id)
	{
		mShell = shell;
		mSections = new QList < Section *>();
		mId = id;
	}

	/*EFigure(QList < Component *> *comps, int id)
	{
		components = new QList < Component *>(comps);
		this->id = id;
	}*/


	void addSection(QList < Component *> *comps)
	{
		mSections->push_front(new Section(comps));
	}
	void addSection(Section *section)
	{
		mSections->push_front(section);
	}

	QList < Component *> *getShell() { return mShell; }
	QList < Section *> *getSections() { return mSections; }

private:
	QList < Component *> *mShell;
	QList < Section *> *mSections;
	int mId;  //id in database
};

class ELink : public EItem
{
public:
	ELink()
	{
		mComponent = new Component();
		mFigure1 = mFigure2 = 0;  //null
	}
	ELink(Component *component)
	{
		mComponent = component;
		mFigure1 = mFigure2 = 0;  //null
	}
	ELink(Component *component, EFigure *figure1, EFigure *figure2)
	{
		mComponent = component;
		mFigure1 = figure1;
		mFigure2 = figure2;
	}
	Component *getComponent() { return mComponent; }
	EFigure *getFigure1() { return mFigure1; }
	EFigure *getFigure2() { return mFigure2; }

private:
	Component *mComponent;
	EFigure *mFigure1, *mFigure2;
};

class Figure
{
	//QList< EItem *> *items;

};

class Link : public ELink
{

};

class CComponent  //Connected Component
{
public:
	CComponent()
	{
		mComps = new QList < Component *> ();
	}

	CComponent(QList < Component *> *components) : mComps(components) { }

	~CComponent()
	{
		delete mComps;
	}
	int size() { return mComps->size(); }
	void removeAll(Component *component)
	{
		mComps->removeAll(component);
	}
	QList < Component *> *getIntersectionList(Component *curComponent)  //old version; better to delete
	{
		QList < Component *> *result = new QList < Component *>();
		for (QList < Component *>::iterator itr = mComps->begin(); itr != mComps->end(); itr++)
		{
			if (Component::intersects(*itr, curComponent))
			{
				result->push_front(*itr);
			}
		}
		return result;
	}
	QList < Component *> *getIntersectionList(QList < Component *> *comps)
	{

	}

	/*QList < Component *> *getIntersectionList(Component *curComponent, Segmentator *segmentator)  //new version
	{
		QList < Component *> *result = new QList < Component *>(segmentator->mInterList[curComponent]);
		for (QList < Component *>::iteartor itr = result->begin(); itr != result->end(); itr++)
		{
			if (!comps->contains(*itr))
			{
				result->erase(itr);
			}
		}
		return res;
	}*/
	void addComponent(Component *newComponent)
	{
		mComps->push_front(newComponent);
	}
	QList < Component *> *getComponents() const { return mComps; }
private:
	QList < Component *> *mComps;
};

class Graph
{
public:
	Graph()
	{
		mMatrix = new IMatrix();
		mInterList = new InterList();
	}
	Graph(QList < Component *> *comps)
	{
		initGraph(comps);
	}
	/*QList < Component *> *depthSearch(Component *component)
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

	QList < CComponent *> *cSegmentation(QList < Component *> *comps)  //splits all components into connected components
	{
		int len = comps->size();
		std::vector<bool> marked(len);
		QList < CComponent *> *cSegments = new QList <CComponent *>();  //list of connected components
		CComponent *cComp;  //current connected component
		for (int i = 0; i < len; i++)
		{
			marked[i] = false;
		}
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
	bool intersects(Component *comp1, Component *comp2)
	{
		return mMatrix->at(std::pair<Component *, Component *>(comp1, comp2));
	}
	IMatrix *getMatrix() { return mMatrix; }
	InterList *getInterList() { return mInterList; }

private:
	void initGraph(QList < Component *> *comps)
	{
		mInterList = new std::map < Component *, QList < Component *> *>();
		//mMatrix = new std::map<pair< Component *, Component * >, bool>();
		mMatrix = new IMatrix();
		QList < Component *> *curList = new QList < Component *>();
		for (QList < Component *>::iterator i = comps->begin(); i != comps->end(); i++)
		{
			for (QList < Component *>::iterator itr = comps->begin(); itr != comps->end(); itr++)
			{
				if (Component::intersects(*i, *itr))
				{
					curList->push_front(*itr);
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
	IMatrix *mMatrix;
	InterList *mInterList;
};

class Segmentator
{
public:
	friend class ESegmentator;
	class ESegmentator  //elementary segmentation of connected component
	{
	public:
		ESegmentator()
		{
			mCComp = new CComponent();
			mFigures = new QList < EFigure *>();
			mLinks = new std::set < ELink *>();
			mGraph = new Graph();
		}
		ESegmentator(CComponent *cComp)
		{
			mCComp = cComp;
			mFigures = new QList < EFigure *>();
			mLinks = new std::set < ELink *>();
			mGraph = new Graph(cComp->getComponents());
		}
		void eSegmentation()  //splits connected component into elementary items (figures and links)
		{
			bool res = makeESegmentation(mCComp);
			if (!res) { return; }			//if error accured
			makeSectionSegmentation();
		}
		void makeSectionSegmentation()
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
		QList < Component *> *getCComp() { return mCComp->getComponents(); }
		QList < EFigure *> *getFigures() { return mFigures; }
		std::set < ELink *> *getLinks() { return mLinks; }
		Graph *getGraph() { return mGraph; }

	private:
		CComponent *mCComp;  //inner connected component
		QList < EFigure *> *mFigures;  //elementary figures
		std::set < ELink *> *mLinks;  //elementary links
		Graph *mGraph;

		void segmentateSections(EFigure *figure, QList < Component *> *innerComps)
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
		CComponent *filter(CComponent *comps)  //filters fixed components
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
		bool makeESegmentation(CComponent *cComp)
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
	};

	Segmentator()
	{
		mComps = new QList < Component *>();
		mGraph = new Graph();
	}
	Segmentator(QList < Component *> *components)
	{
		mComps = components;
		mGraph = new Graph(components);
	}
	~Segmentator()
	{
		delete mComps;
		delete mGraph;
	}
	void makeSegmentation(QList < Figure *> *&figures, QList < Link *> *&links)
	{
		ESegmentator *eSegmentator = new ESegmentator(new CComponent(mComps));
		eSegmentator->eSegmentation();
		ASegmentator *aSegmentator = new ASegmentator(eSegmentator);
		aSegmentator->aSegmentation();
		figures = aSegmentator->mFigures;
		links = aSegmentator->mLinks;
		delete eSegmentator;
		delete aSegmentator;
	}
private:

	QList < Component *> *mComps;  //list of all components
	Graph *mGraph;

	/*bool intersects(Component *comp1, Component *comp2)
	{
		return mMatrix->at(std::pair<Component *, Component *>(comp1, comp2));
	}
	QList < Component *> *getIntersectionList(Component *comp)
	{
		return mInterList->at(comp);
	}*/
	static QList < Component *> *getOuterShell(QList < Component *> *comps)  //comps are connected
	{
		/*  here follows some actions  */
	}
	static QList < Component *> *getInnerShell(QList < Component *> *comps)  //comps are connected
	{
		/*  here follows some actions  */
	}
	class ASegmentator
	{
	public:
		ASegmentator()
		{
			mFigures = new QList < Figure *>();
			mLinks = new QList < Link *>();
		}
		ASegmentator(ESegmentator *eSegmentator) : eSegmentator(eSegmentator) { }
		void aSegmentation()
		{
		}

		QList < Figure *> *mFigures;
		QList < Link *> *mLinks;

	private:
		ESegmentator *eSegmentator;
	};
};

class Field
{
public:
	Field()
	{
		mFigures = new QList < Figure *>();
		mLinks = new QList < Link *>();
		mComponents = new QList < Component *>();
	}
	Field(QList < Component *> *components)
	{
		mComponents = new QList < Component *>(*components);
		Segmentator *segmentator = new Segmentator(mComponents);
		segmentator->makeSegmentation(mFigures, mLinks);
		delete segmentator;
	}
	~Field()
	{
		delete mFigures;
		delete mLinks;
		delete mComponents;
	}

private:
	QList < Figure *> *mFigures;
	QList < Link *> *mLinks;
	QList < Component *> *mComponents;  //list of all components
};
