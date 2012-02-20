#include "formsegmentator.h"
#include <QMap>
#include "stdlib.h"
#include <QDebug>


FormSegmentator::FormSegmentator(Bitmap *bitmap)
{
    mBitmap = bitmap;
    analyzeBitmap();
    //initComponents();
    qDebug() << "components initialized";
}

void FormSegmentator::analyzeBitmap()
{
    mCurrentDiagram = new Diagram();
    for (int i = 0; i < mBitmap->size(); i ++)
    {
        for (int j = 0; j < mBitmap->at(i).size(); j++) {
            initComponent(i, j);
            if (!mCurrentDiagram->empty()) {
                mCurrentDiagram->analyze();
                mAllComponents.push_back(*mCurrentDiagram);
                mCurrentDiagram = new Diagram();
            }
        }
    }
}
void FormSegmentator::initComponent(int x, int y)
{
    if (mBitmap->at(x).at(y) >= 0)
        return;
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
        if (x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0
            && x1 < gridWidth && y1 < gridHeight && x2 < gridWidth && y2 < gridHeight
            && mBitmap->at(x1).at(y1) != 0 && mBitmap->at(x2).at(y2) != 0) {
            qDebug() << x << y << "corners" << x1 << y1 << x2 << y2;
            return;
        }
        cornerX = nextCornerX;
        cornerY = nextCornerY;
    }
    if ((y == 0 || mBitmap->at(x).at(y - 1) == 0) &&
        (y == gridHeight - 1 || mBitmap->at(x).at(y + 1) == 0) &&
        (x == 0 || mBitmap->at(x - 1).at(y) == 0) &&
        (x == gridWidth - 1 || mBitmap->at(x + 1).at(y) ==0)) {
        //TODO:: new method
        for (int i = std::max(0, y - 1); i <= std::min(gridHeight - 1, y + 1); i ++) {
            for (int j = std::max(0, x - 1); j <= std::min(gridWidth - 1, x + 1); j ++)
                initComponent(j, i);
        }
        return;
    }
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
                mBitmap->at(x + nextNeighbourX)[y + nextNeighbourY] != 0) {
            int x1 = x + neighbourX - neighbourY;
            int y1 = y + neighbourX + neighbourY;
            int x2 = x - neighbourX;
            int y2 = y - neighbourY;
            int x3 = x - neighbourX + neighbourY;
            int y3 = y - neighbourX - neighbourY;
            int x4 = x + neighbourY;
            int y4 = y - neighbourX;
            if ((x1 >= 0 && x1 < gridWidth && y1 >= 0 && y1 < gridHeight && mBitmap->at(x1)[y1] != 0) ||
                    (x2 >= 0 && x2 < gridWidth && y2 >= 0 && y2 < gridHeight && mBitmap->at(x2)[y2] != 0) ||
                    (x3 >= 0 && x3 < gridWidth && y3 >= 0 && y3 < gridHeight && mBitmap->at(x3)[y3] != 0) ||
                    (x4 >= 0 && x4 < gridWidth && y4 >= 0 && y4 < gridHeight && mBitmap->at(x4)[y4] != 0)) {
                return;
            }

        }
        neighbourX = nextNeighbourX;
        neighbourY = nextNeighbourY;
    }
    for (int i = std::max(0, y - 1); i <= std::min(gridHeight - 1, y + 1); i ++) {
        for (int j = std::max(0, x - 1); j <= std::min(gridWidth - 1, x + 1); j ++)
            initComponent(j, i);
    }
}

Diagram FormSegmentator::getComponent(const QPoint &point)
{
    Diagram diagram;
    if (point.x() < mBitmap->xLeft() || point.x() > mBitmap->xRight()
        || point.y() < mBitmap->yUpper() || point.y() > mBitmap->yLower()) {
        return diagram;
    }
    int x = (point.x() - mBitmap->xLeft()) / hStep;
    int y = (point.y() - mBitmap->yUpper()) / hStep;
    int component = mBitmap->at(x)[y];
    if (component == 0)
        return diagram;
    foreach (Diagram component, mAllComponents) {
        if (component.contains(SquarePos(x, y))) {
            return component;
        }
    }
    return diagram;
}

QList<Diagram> FormSegmentator::getAllComponents()
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
    int withNeighbour = componentWithNeighbour();
    while (withNeighbour >= 0) {
        Diagram diagram = mAllComponents.at(withNeighbour);
        mAllComponents.removeAt(withNeighbour);;
        bool isBeginDiagram1 = false;
        bool isBeginDiagram2 = false;
        int mergeDiagram = -1;
        int derDiff = 3;
        for (int i = 0; i < mAllComponents.size(); i++) {
            Diagram checkDiagram = mAllComponents.at(i);
            for (int j = 0; j <= 1; j ++) {
                for (int k = 0; k <= 1; k ++){
                    int num1 = (j == 1) ? 0 : (diagram.size() - 1);
                    int num2 = (k == 1) ? 0 : (checkDiagram.size() - 1);
                    QPair<double, double> diagramDer =
                            (j == 1) ? diagram.getDerivativeBegin() : diagram.getDerivativeBack();
                    QPair<double, double> checkDiagramDer =
                            (k == 1) ? checkDiagram.getDerivativeBegin() : checkDiagram.getDerivativeBack();
                    if (diagram.at(num1).dist(checkDiagram.at(num2)) <= neighbourhoodRad
                        && abs(diagramDer.first + checkDiagramDer.first)
                        + abs(diagramDer.second + checkDiagramDer.second) < derDiff) {
                        derDiff = abs(diagramDer.first + checkDiagramDer.first)
                                  + abs(diagramDer.second + checkDiagramDer.second);
                        qDebug() << diagramDer.first << diagramDer.second;
                        mergeDiagram = i;
                        isBeginDiagram1 = (j == 1) ? true : false; //I think it could be shorter
                        isBeginDiagram2 = (k == 1) ? true : false;
                    }
                }
            }
        }
        if (mergeDiagram >= 0) {
            Diagram currentDiagram = mAllComponents.at(mergeDiagram);
            diagram = merge(diagram, currentDiagram, isBeginDiagram1, isBeginDiagram2);
            mAllComponents.removeAt(mergeDiagram);
            qDebug() << "merge";
        }
        mAllComponents.push_back(diagram);
        withNeighbour = componentWithNeighbour();
    }
}

Diagram FormSegmentator::merge(const Diagram &diagram1, const Diagram &diagram2,
                               bool isBegin1, bool isBegin2)
{
    Diagram finalDiagram;
    if (isBegin1 && !isBegin2) {
        finalDiagram = diagram2;
        finalDiagram.append(diagram1);
    }
    else if (!isBegin1 && isBegin2) {
        finalDiagram = diagram1;
        finalDiagram.append(diagram2);
    }
    else if (isBegin1 && isBegin2) {
        finalDiagram = diagram1;
        foreach (SquarePos pos, diagram2) {
            finalDiagram.push_front(pos);
        }
    }
    else {
        finalDiagram = diagram1;
        for (int i = diagram2.size() - 1; i >= 0; i --) {
            finalDiagram.push_back(diagram2.at(i));
        }
    }
    finalDiagram.analyze();
    return finalDiagram;
}

int FormSegmentator::componentWithNeighbour()
{
    for (int i = 0; i < mAllComponents.size() - 1; i ++) {
        Diagram diagram = mAllComponents.at(i);
        for (int j = i + 1; j < mAllComponents.size(); j ++) {
            Diagram neighbour = mAllComponents.at(j);
            if (diagram.at(0).dist(neighbour.at(0)) <= neighbourhoodRad
                || diagram.back().dist(neighbour.at(0)) <= neighbourhoodRad
                || diagram.at(0).dist(neighbour.back()) <= neighbourhoodRad
                || diagram.back().dist(neighbour.back()) <= neighbourhoodRad) {
                return i;
            }
        }
    }
    return  -1;
}
