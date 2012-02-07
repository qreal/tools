#include "formsegmentator.h"
#include <QMap>
#include "stdlib.h"
#include <QDebug>


FormSegmentator::FormSegmentator(Bitmap *bitmap)
{
    mBitmap = bitmap;
    initComponents();
    qDebug() << "components initialized";
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
    QMap<int, Diagram> components;
    for (int i = 0; i < mBitmap->size(); i ++) {
        if (mBitmap->at(i).empty()) {
            return;
        }
        for (int j = 0; j < mBitmap->at(i).size(); j ++) {
            int currentComponentNum = mBitmap->at(i)[j];
            if (components.keys().contains(currentComponentNum)) {
                components[currentComponentNum].insertPos(SquarePos(i, j));
            }
            else if (currentComponentNum != 0) {
                Diagram newComponent;
                newComponent.insertPos(SquarePos(i, j));
                components.insert(currentComponentNum, newComponent);
            }
        }
    }
    mAllComponents = components.values();
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
        foreach (Diagram checkDiagram, mAllComponents) {
            if (diagram.at(0).dist(checkDiagram.at(0)) <= neighbourhoodRad
                && abs(diagram.getDerivativeBegin() + checkDiagram.getDerivativeBegin()) < derDiff) {
                derDiff = abs(diagram.getDerivativeBegin() + checkDiagram.getDerivativeBegin());
                mergeDiagram = checkDiagram.ID();
                isBegin = true;
            }
            if (diagram.at(0).dist(checkDiagram.back()) <= neighbourhoodRad
                && abs(diagram.getDerivativeBegin() + checkDiagram.getDerivativeBack()) < derDiff) {
                derDiff = abs(diagram.getDerivativeBegin() + checkDiagram.getDerivativeBack());
                mergeDiagram = checkDiagram.ID();
                isBegin = false;
            }
        }
        if (mergeDiagram > 0) {
            int i = 0;
            Diagram currentDiagram = mAllComponents.at(i);
            while (i < mAllComponents.size() && currentDiagram.ID() != mergeDiagram) {
                //Bad!!! Very very bad!!! Cause order of SquarePos is important!!!
                //TODO:: kill this
                diagram.append(currentDiagram);
                mAllComponents.removeAt(i);
            }
        }
        //TODO: kill Indian code
        isBegin = false;
        mergeDiagram = -1;
        derDiff = 5000;
        foreach (Diagram checkDiagram, mAllComponents) {
            if (diagram.back().dist(checkDiagram.at(0)) <= neighbourhoodRad
                && abs(diagram.getDerivativeBack() + checkDiagram.getDerivativeBegin()) < derDiff) {
                derDiff = abs(diagram.getDerivativeBack() + checkDiagram.getDerivativeBegin());
                mergeDiagram = checkDiagram.ID();
                isBegin = true;
            }
            if (diagram.back().dist(checkDiagram.back()) <= neighbourhoodRad
                && abs(diagram.getDerivativeBegin() + checkDiagram.getDerivativeBack()) < derDiff) {
                derDiff = abs(diagram.getDerivativeBack() + checkDiagram.getDerivativeBack());
                mergeDiagram = checkDiagram.ID();
                isBegin = false;
            }
        }
        if (mergeDiagram > 0) {
            int i = 0;
            Diagram currentDiagram = mAllComponents.at(i);
            while (i < mAllComponents.size() && currentDiagram.ID() != mergeDiagram) {
                //Bad!!! Very very bad!!! Cause order of SquarePos is important!!!
                //TODO:: kill this
                diagram.append(currentDiagram);
                mAllComponents.removeAt(i);
            }
        }
        newComponents.push_back(diagram);;
    }
    mAllComponents = newComponents;
}
