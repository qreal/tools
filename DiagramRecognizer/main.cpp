#include <QtGui/QApplication>
#include "diagramRecognizer.h"
#include <field.h>
#include <iostream>
#include <cstdio>
#include <graph.h>
#include <segmentator.h>

using namespace std;
class Read
{
public:
	static void readFile(QList < Component *> *comps)
	{
		FILE *f = fopen("test4.txt", "r");
		if (f == 0) { return; }
		int num, n;
		while (true)
		{
			fscanf(f, "%d %d\n", &num, &n);
			if ((num == 0) && (n == 0)) { break; }
			Component *component = new Component();
			component->num = num;
			for (int i = 0; i < n; i++)
			{
				int x, y;
				fscanf(f, "%d %d\n", &x, &y);
				component->push_back(SquarePos(x, y));
			}
			comps->push_back(component);
		}
	}
};
int main()
{
	//QApplication a(argc, argv);
	//DiagramRecognizer widget;
	//widget.setGeometry(100, 100, 500, 355);
	//widget.show();
	QList < Component *> *comps = new QList < Component *>();
	Read::readFile(comps);
	Graph g(comps);
	g.eraseEdge(comps->first());
	comps->removeFirst();
	QList < Component *> *shell = Segmentator::getInnerShell(comps->first(), comps, g);
	for (QList < Component *>::iterator i = shell->begin(); i != shell->end(); i++)
	{
		cout << (*i)->num << " ";
	}
	/*QList < QList < Component *> *> *segm = g.cSegmentation(comps, g);
	for (QList < QList < Component *> *>::iterator i = segm->begin(); i != segm->end(); i++)
	{
		QList < Component *> *list = *i;
		for (QList < Component *>::iterator itr = list->begin(); itr != list->end(); itr++)
		{
			cout << (*itr)->num << " ";
		}
		cout << endl;
	}*/
	//Component *cur = comps->first();
	//Field f(comps);
	//g.eraseEdge(cur);
	/*InterList *iList = g.getInterList();
	for (InterList::iterator i = iList->begin(); i != iList->end(); i++)
	{
		Component *cur = (*i).first;
		cout << (*i).first->num << ": ";
		QList < Component *> *list = (*i).second;
		for (QList < Component *>::iterator p = list->begin(); p != list->end(); p++)
		{
			cout << (*p)->num << " ";
		}
		cout << endl;
	}*/
	return 0;
}
