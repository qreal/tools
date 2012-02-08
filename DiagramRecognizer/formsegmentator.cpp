#include "formsegmentator.h"
#include <QMap>
#include "stdlib.h"
#include <QDebug>


FormSegmentator::FormSegmentator(Bitmap *bitmap)
{
    mBitmap = bitmap;
    analyzeBitmap();
    initComponents();
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
    return;
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

void FormSegmentator::initComponents()
{
    foreach (Diagram diagram, mAllComponents) {
        diagram.analyze();
    }
}

void FormSegmentator::uniteComponents()
{
    QList<Diagram> newComponents;
    while (!mAllComponents.empty()) {
        Diagram diagram = mAllComponents.back();
        mAllComponents.pop_back();
        bool isBegin = false;
        int mergeDiagram = -1;
        int derDiff = 5000;
        QPair<double, double> diagramDer1 = diagram.getDerivativeBegin();
        QPair<double, double> diagramDer2 = diagram.getDerivativeBack();
        foreach (Diagram checkDiagram, mAllComponents) {
            QPair<double, double> checkDiagramDer1 = checkDiagram.getDerivativeBegin();
            QPair<double, double> checkDiagramDer2 = checkDiagram.getDerivativeBack();
            if (diagram.at(0).dist(checkDiagram.at(0)) <= neighbourhoodRad
                && abs(diagramDer1.first + checkDiagramDer1.first)
                + abs(diagramDer1.second + checkDiagramDer1.second) < derDiff) {
                derDiff = abs(diagramDer1.first + checkDiagramDer1.first)
                          + abs(diagramDer1.second + checkDiagramDer1.second);
                mergeDiagram = checkDiagram.ID();
                isBegin = true;
            }
            if (diagram.at(0).dist(checkDiagram.back()) <= neighbourhoodRad
                && abs(diagramDer1.first + checkDiagramDer2.first)
                + abs(diagramDer1.second + checkDiagramDer2.second) < derDiff) {
                derDiff = abs(diagramDer1.first + checkDiagramDer2.first)
                          + abs(diagramDer1.second + checkDiagramDer2.second);
                mergeDiagram = checkDiagram.ID();
                isBegin = false;
            }
        }
        if (mergeDiagram > 0) {
            int i = 0;
            while (i < mAllComponents.size() && mAllComponents.at(i).ID() != mergeDiagram) {
                i++;
            }
            //Bad!!! Very very bad!!! Cause order of SquarePos is important!!!
            //TODO:: kill this
            Diagram currentDiagram = mAllComponents.at(i);
            diagram.append(currentDiagram);
            mAllComponents.removeAt(i);
        }
        //TODO: kill Indian code
        isBegin = false;
        mergeDiagram = -1;
        derDiff = 5000;
        foreach (Diagram checkDiagram, mAllComponents) {
            QPair<double, double> checkDiagramDer1 = checkDiagram.getDerivativeBegin();
            QPair<double, double> checkDiagramDer2 = checkDiagram.getDerivativeBack();
            if (diagram.back().dist(checkDiagram.at(0)) <= neighbourhoodRad
                && abs(diagramDer2.first + checkDiagramDer1.first)
                + abs(diagramDer2.second + checkDiagramDer1.second) < derDiff) {
                derDiff = abs(diagramDer2.first + checkDiagramDer1.first)
                          + abs(diagramDer2.second + checkDiagramDer1.second);
                mergeDiagram = checkDiagram.ID();
                isBegin = true;
            }
            if (diagram.back().dist(checkDiagram.back()) <= neighbourhoodRad
                && abs(diagramDer2.first + checkDiagramDer2.first)
                + abs(diagramDer2.second + checkDiagramDer2.second) < derDiff) {
                derDiff = abs(diagramDer2.first + checkDiagramDer2.first)
                          + abs(diagramDer2.second + checkDiagramDer2.second);
                mergeDiagram = checkDiagram.ID();
                isBegin = false;
            }
        }
        if (mergeDiagram > 0) {
            int i = 0;
            while (i < mAllComponents.size() && mAllComponents.at(i).ID() != mergeDiagram) {
                i++;
            }
            //Bad!!! Very very bad!!! Cause order of SquarePos is important!!!
            //TODO:: kill this
            Diagram currentDiagram = mAllComponents.at(i);
            diagram.append(currentDiagram);
            mAllComponents.removeAt(i);
        }
        newComponents.push_back(diagram);;
    }
    mAllComponents = newComponents;
}
