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
		FILE *f = fopen("test3.txt", "r");
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
int main(int argc, char *argv[])
{
	//QApplication a(argc, argv);
	//DiagramRecognizer widget;
	//widget.setGeometry(100, 100, 500, 355);
	//widget.show();
	QList < Component *> *comps = new QList < Component *>();
	Read::readFile(comps);
	Graph g(comps);
	/*QList < Component *>::iterator i = comps->begin();
	i++; i++;
	while (i != comps->end())
	{
		std::cout << *i << std::endl;
		comps->erase(i);
		std::cout << *i << std::endl;
		i++;
	}*/
	//comps->erase(comps->end()--);
	std::set < Component *> *newComps = new std::set < Component *>();
	std::set<Component *> *shell = Segmentator::getOuterShell(comps, g);
	for (std::set<Component *>::const_iterator i = shell->begin(); i != shell->end(); i++)
	{
		std::cout << (*i)->num << std::endl;
		newComps->insert(*i);
	}
	std::cout << "Lol" << std::endl;
	std::set<Component *> *comp = Segmentator::extractBridge(shell, g);
	for (std::set<Component *>::const_iterator i = comp->begin(); i != comp->end(); i++)
	{
		std::cout << (*i)->num << std::endl;
	}
	/*std::set < Component *> *list = g.getIList(SquarePos(3, 4));
	cout << list->size() << endl;
	for (std::set < Component *>::iterator i = list->begin(); i != list->end(); i++)
	{
		cout << (*i)->num << endl;
	}*/
	int x = 0;
	int y = 10;
	y = x + y;
	return 0;
}
