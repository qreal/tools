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
		FILE *f = fopen("test2.txt", "r");
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
	QList < Component *>::iterator i = comps->begin();
	/*i++; i++; i++; i++; i++;
	comps->erase(i);
	i++; i++;
	comps->erase(i);*/

	//Graph g(comps);
	//QList < CComponent *> *cComps = g.cSegmentation(comps);
	//Segmentator s(comps);
	//SquarePos q = Component::center(comps);
	//cout << q.first << " " << q.second << endl;
	//QList < Component *> *shell = Segmentator::getOuterShell(cComps->first()->getComponents(), s.getGraph());
	//for (QList < Component *>::const_iterator i = shell->begin(); i != shell->end(); i++)
	//{
	//	cout << (*i)->num << " ";
	//}
	//Segmentator::ESegmentator *segm = new Segmentator::ESegmentator(*(cComps->begin()));
	//segm->eSegmentation();

	//Segmentator::ESegmentator *segm = new Segmentator::ESegmentator();
	//cout << cComps->size() << endl;
	SquarePos point = SquarePos(4, 4);
	cout << Field::pointInContur(point, comps);
	int x = 0;
	int y = 10;
	y = x + y;
	return 0;
}
