#include "formSegmentator.h"
#include <QMap>
#include "stdlib.h"
#include <QDebug>


FormSegmentator::FormSegmentator(Bitmap *bitmap)
{
	mBitmap = bitmap;
	analyzeBitmap();
}
void FormSegmentator::analyze(QList<Component> &objects, QList<Component> &edges)
{
	uniteComponents();
	objects = getObjects();
	edges = getEdges();
	return;
}

void FormSegmentator::analyzeBitmap()
{
	mCurrentDiagram = new Component();
	for (int i = 0; i < mBitmap->size(); i ++) {
		for (int j = 0; j < mBitmap->at(i).size(); j++) {
			initComponent(i, j);
			if (!mCurrentDiagram->empty()) {
				mCurrentDiagram->analyze();
				mAllComponents.push_back(*mCurrentDiagram);
				mCurrentDiagram = new Component();
			}
		}
	}
}
void FormSegmentator::initComponent(int x, int y) //находит компоненту, начиная с точки (x, y)
{
	if (mBitmap->at(x).at(y) >= 0) {
		return;
	}
	mCurrentDiagram->insertPos(SquarePos(x, y));
	mBitmap->operator [](x)[y] = 1;
	int gridWidth = mBitmap->size();
	int gridHeight = mBitmap->at(x).size();
	int cornerX = -1;
	int cornerY = -1;
	for (int i = 0; i < 4; i ++) {
		int nextCornerX = - cornerY;
		int nextCornerY = cornerX;
		int x1 = x + cornerX;
		int y1 = y + cornerY;
		int x2 = x + nextCornerX;
		int y2 = y + nextCornerY;
		if (x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0 && x1 < gridWidth
				&& y1 < gridHeight && x2 < gridWidth && y2 < gridHeight
				&& mBitmap->at(x1).at(y1) != 0 && mBitmap->at(x2).at(y2) != 0)
		{
			return;
		}
		cornerX = nextCornerX;
		cornerY = nextCornerY;
	}
	//do we really need this condition?
	//	if ((y == 0 || mBitmap->at(x).at(y - 1) == 0) &&
	//		(y == gridHeight - 1 || mBitmap->at(x).at(y + 1) == 0) &&
	//		(x == 0 || mBitmap->at(x - 1).at(y) == 0) &&
	//		(x == gridWidth - 1 || mBitmap->at(x + 1).at(y) ==0))
	//	{
	//		//TODO:: new method
	//		for (int i = std::max(0, y - 1);
	//			i <= std::min(gridHeight - 1, y + 1); i ++)
	//		{
	//			for (int j = std::max(0, x - 1);
	//				j <= std::min(gridWidth - 1, x + 1); j ++)
	//			{
	//				initComponent(j, i);
	//			}
	//		}
	//		return;
	//	}
	int neighbourX = 0;
	int neighbourY = 1;
	for (int i = 0; i < 4; i ++) {
		int nextNeighbourX = - neighbourY;
		int nextNeighbourY = neighbourX;
		if (x + neighbourX >= 0 && y + neighbourY >= 0 &&
				x + neighbourX < gridWidth && y + neighbourY < gridHeight &&
				x + nextNeighbourX >= 0 && y + nextNeighbourY >= 0 &&
				x + nextNeighbourX < gridWidth && y + nextNeighbourY < gridHeight &&
				mBitmap->at(x + neighbourX)[y + neighbourY] != 0 &&
				mBitmap->at(x + nextNeighbourX)[y + nextNeighbourY] != 0)
		{
			int x1 = x + neighbourX - neighbourY;
			int y1 = y + neighbourX + neighbourY;
			int x2 = x - neighbourX;
			int y2 = y - neighbourY;
			int x3 = x - neighbourX + neighbourY;
			int y3 = y - neighbourX - neighbourY;
			int x4 = x + neighbourY;
			int y4 = y - neighbourX;
			if ((x1 >= 0 && x1 < gridWidth && y1 >= 0
				 && y1 < gridHeight && mBitmap->at(x1)[y1] != 0) ||
					(x2 >= 0 && x2 < gridWidth && y2 >= 0
					 && y2 < gridHeight && mBitmap->at(x2)[y2] != 0) ||
					(x3 >= 0 && x3 < gridWidth && y3 >= 0
					 && y3 < gridHeight && mBitmap->at(x3)[y3] != 0) ||
					(x4 >= 0 && x4 < gridWidth && y4 >= 0 &&
					 y4 < gridHeight && mBitmap->at(x4)[y4] != 0))
			{
				return;
			}

		}
		neighbourX = nextNeighbourX;
		neighbourY = nextNeighbourY;
	}
	for (int i = std::max(0, y - 1); i <= std::min(gridHeight - 1, y + 1); i ++) {
		for (int j = std::max(0, x - 1);
			 j <= std::min(gridWidth - 1, x + 1); j ++)
		{
			initComponent(j, i);
		}
	}
}

Component FormSegmentator::component(const QPoint &point) const
{
	Component diagram;
	if (point.x() < mBitmap->xLeft() || point.x() > mBitmap->xRight()
			|| point.y() < mBitmap->yUpper() || point.y() > mBitmap->yLower())
	{
		return diagram;
	}
	int x = (point.x() - mBitmap->xLeft()) / hStep;
	int y = (point.y() - mBitmap->yUpper()) / hStep;
	int component = mBitmap->at(x)[y];
	if (component == 0) {
		return diagram;
	}
	foreach (Component const &component, mAllComponents) {
		if (component.contains(SquarePos(x, y))) {
			return component;
		}
	}
	return diagram;
}

QList<Component> FormSegmentator::getAllComponents() const
{
	return mAllComponents;
}

//void FormSegmentator::initComponents()
//{
//    for (int i = 0; i < mAllComponents.size(); i ++) {
//        mAllComponents.at(i).analyze();
//    }
//}

void FormSegmentator::uniteComponents()
{
	int i = 0;
	while (i < mAllComponents.size()) {
		if (mAllComponents.at(i).isNegligible()) {
			mAllComponents.removeAt(i);
		}
		else {
			i ++;
		}
	}
	uniteCorners();
	uniteSmoothFigure();
	uniteCornersWithEdges();
}

QList<Component> FormSegmentator::getObjects() const
{
	QList<Component> objects;
	foreach (Component const &diagram, mAllComponents) {
		if (diagram.hasSelfIntersection()) {
			objects.push_back(diagram);
		}
	}
	return objects;
}

QList<Component> FormSegmentator::getEdges() const
{
	QList<Component> edges;
	foreach (Component const &diagram, mAllComponents) {
		if (!diagram.hasSelfIntersection()) {
			edges.push_back(diagram);
		}
	}
	return edges;
}

void FormSegmentator::uniteCorners()
{
	bool wasUnited = true;
	while (wasUnited) {
		bool isBeginDiagram1 = false;
		bool isBeginDiagram2 = false;
		int mergeDiagram1 = -1;
		int mergeDiagram2 = -1;
		for (int i = 0; i < mAllComponents.size(); i ++) {
			Component diagram = mAllComponents.at(i);
			if (diagram.back().dist(diagram.at(0)) <= neighbourhoodRad) {
				continue;
			}
			for (int j = 0; j <= 1; j ++) {
				int pos = (j == 1) ? 0 : (diagram.size() - 1);
				SquarePos currentPos = diagram.at(pos);
				int numDiagram = neighbourPos(currentPos, i);
				if (numDiagram < 0) {
					continue;
				}
				mergeDiagram1 = i;
				mergeDiagram2 = numDiagram;
				isBeginDiagram1 = (j == 1);
				SquarePos firstPosDiagram2 = mAllComponents.at(numDiagram).at(0);
				isBeginDiagram2 =
						currentPos.dist(firstPosDiagram2) <= neighbourhoodRad;
			}
		}
		wasUnited = isMergedDiagrams(mergeDiagram1, mergeDiagram2,
									 isBeginDiagram1, isBeginDiagram2);
	}
}
int  FormSegmentator::neighbourPos(const SquarePos &pos, int diagramNum) const
{
	int num = -1;
	for (int i = 0; i < mAllComponents.size(); i ++) {
		Component diagram = mAllComponents.at(i);
		if ((i != diagramNum && (num >= 0 &&
								 (pos.dist(diagram.at(0)) <= neighbourhoodRad ||
								  pos.dist(diagram.back()) <= neighbourhoodRad))) ||
				(pos.dist(diagram.at(0)) <= neighbourhoodRad &&
				 pos.dist(diagram.back()) <= neighbourhoodRad))
		{
			return -1;
		}
		if (diagramNum != i && (pos.dist(diagram.at(0)) <= neighbourhoodRad ||
								pos.dist(diagram.back()) <= neighbourhoodRad))
		{
			num = i;
		}
	}
	return num;
}

bool FormSegmentator::isMergedDiagrams(int i, int j,
									   bool isBeginDiagram1, bool isBeginDiagram2)
{
	if (i < 0 || j < 0) {
		return false;
	}
	Component currentDiagram1 = mAllComponents.at(i);
	Component currentDiagram2 = mAllComponents.at(j);
	mAllComponents.removeAt(std::min(i, j));
	mAllComponents.removeAt(std::max(i, j) - 1);
	currentDiagram1.insertDiagram(currentDiagram2,
								  isBeginDiagram1, isBeginDiagram2);
	mAllComponents.push_back(currentDiagram1);
	return true;
}

void FormSegmentator::uniteSmoothFigure()
{
	bool wasUnited = true;
	while (wasUnited) {
		bool isBeginDiagram1 = false;
		bool isBeginDiagram2 = false;
		int mergeDiagram1 = -1;
		int mergeDiagram2 = -1;
		double minDerDiff = 0.8;
		for (int g = 0; g < mAllComponents.size() - 1; g++) {
			Component diagram = mAllComponents.at(g);
			for (int i = g + 1; i < mAllComponents.size(); i++) {
				Component checkDiagram = mAllComponents.at(i);
				for (int j = 0; j <= 1; j ++) {
					for (int k = 0; k <= 1; k ++) {
						int num1 = (j == 1) ? 0 : (diagram.size() - 1);
						int num2 = (k == 1) ? 0 : (checkDiagram.size() - 1);
						QPair<double, double> diagramDer = (j == 1) ?
									diagram.derivativeBegin() : diagram.derivativeBack();
						QPair<double, double> checkDiagramDer = (k == 1) ?
									checkDiagram.derivativeBegin() : checkDiagram.derivativeBack();
						double derDiff = abs(diagramDer.first +
											 checkDiagramDer.first) +
								abs(diagramDer.second + checkDiagramDer.second);
						if (diagram.at(num1).dist(checkDiagram.at(num2))
								> neighbourhoodRad || derDiff >= minDerDiff)
						{
							continue;
						}
						minDerDiff = derDiff;
						mergeDiagram1 = g;
						mergeDiagram2 = i;
						isBeginDiagram1 = (j == 1);
						isBeginDiagram2 = (k == 1);
					}
				}
			}
		}
		wasUnited = isMergedDiagrams(mergeDiagram1, mergeDiagram2,
									 isBeginDiagram1, isBeginDiagram2);
	}
}

//todo:: make this method more smart, maybe it would be unite some components incorrectly
void FormSegmentator::uniteCornersWithEdges()
{
	bool wasUnited = true;
	while (wasUnited) {
		wasUnited = false;
		int i = 0;
		while (i < mAllComponents.size() && !wasUnited) {
			// unnecessary because off condition to cycle at findCycle method
			if (mAllComponents.at(i).at(0).dist(mAllComponents.at(i).back())
					<= neighbourhoodRad) {
				i++;
				continue;
			}
			QList<QPair<int, bool> > polygon;
			polygon.push_back(QPair<int, bool>(i, true));
			polygon = findCycle(polygon);
			qDebug() << "found cycle" << polygon.size();
			if (polygon.empty()) {
				i++;
				continue;
			}
			wasUnited = true;
			while (polygon.size() > 1) {
				//TODO:: add comments!!!
				QPair<int, bool> firstMerge = polygon.at(0);
				QPair<int, bool> secondMerge = polygon.at(1);
				polygon.pop_front();
				polygon.pop_front();
				// !firstMerge.second = false
				isMergedDiagrams(firstMerge.first, secondMerge.first,
								 !firstMerge.second, secondMerge.second);
				for (int j = 0; j < polygon.size(); j ++) {
					if (polygon.at(j).first >= firstMerge.first) {
						polygon[j].first --;
					}
					if (polygon.at(j).first >= secondMerge.first) {
						polygon[j].first --;
					}
				}
				// push to polygon merged components, the first component always has true value
				polygon.push_front(QPair<int, bool>(mAllComponents.size() - 1, true));
			}
		}

	}
}

// true if diagram intersects previous diagram at the begin
QList<QPair<int, bool> > FormSegmentator::findCycle(
		QList<QPair<int, bool> > const &polygon)
{
	Component firstDiagram = mAllComponents.at(polygon.at(0).first);
	Component lastDiagram = mAllComponents.at(polygon.back().first);
	int posFirst = polygon.at(0).second ? 0 : firstDiagram.size() - 1;
	int posLast = (!polygon.back().second) ? 0 : lastDiagram.size() - 1;
	int maxCycleSize = mAllComponents.size();
	QList<QPair<int, bool> > cycle;
	if (firstDiagram.at(posFirst).dist(lastDiagram.at(posLast))
			<= neighbourhoodRad)
	{
		return polygon;
	}
	for (int i = 0; i < mAllComponents.size(); i ++) {
		Component diagram = mAllComponents.at(i);
		if (diagram.back().dist(diagram.at(0)) <= neighbourhoodRad
				|| contains(polygon, i))
		{
			continue;
		}
		if (diagram.at(0).dist(lastDiagram.at(posLast)) <= neighbourhoodRad) {
			QList<QPair<int, bool> > newPolygon = polygon;
			newPolygon.push_back(QPair<int, bool>(i, true));
			newPolygon = findCycle(newPolygon);
			if (newPolygon.size() > 1 && newPolygon.size() <= maxCycleSize) {
				cycle = newPolygon;
				maxCycleSize = newPolygon.size();
			}
		}
		if (diagram.back().dist(lastDiagram.at(posLast)) <= neighbourhoodRad) {
			QList<QPair<int, bool> > newPolygon = polygon;
			newPolygon.push_back(QPair<int, bool>(i, false));
			newPolygon = findCycle(newPolygon);
			if (!newPolygon.empty() && newPolygon.size() <= maxCycleSize) {
				cycle = newPolygon;
				maxCycleSize = newPolygon.size();
			}
		}
	}
	return cycle;
}

bool FormSegmentator::contains(const QList<QPair<int, bool> > &polygon, int i) const
{
	for (int k = 0; k < polygon.size(); k ++) {
		if (i == polygon.at(k).first) {
			return true;
		}
	}
	return false;
}
