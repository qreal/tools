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
		FILE *f = fopen("test1.txt", "r");
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
	QList < CComponent *> *cComps = g.cSegmentation(comps);
	Segmentator::ESegmentator *segm = new Segmentator::ESegmentator();
	int x = 0;
	int y = 10;
	y = x + y;
	return 0;
}
