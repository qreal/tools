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
            if (components.contains(currentComponentNum)) {
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
        //diagram.analyze();
    }
}

void FormSegmentator::uniteComponents()
{
    QList<Diagram> newComponents;
    while (!mAllComponents.empty()) {
        Diagram diagram = mAllComponents.back();
        mAllComponents.pop_back();
        foreach (Diagram checkDiagram, mAllComponents) {
            diagram.checkNeighbour(checkDiagram);
        }
        newComponents.push_back(diagram);;
    }
    mAllComponents = newComponents;
}
