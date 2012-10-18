#pragma once
#include "bitmap.h"

class FormSegmentator
{
public:
    FormSegmentator(Bitmap *bitmap);

    //further follows new methods
    void analyze(QList<Component> &objects, QList<Component> &edges);
    void uniteComponents();
    QList<Component> getAllComponents() const;
    QList<Component> getObjects() const;
    QList<Component> getEdges() const;
    Component component(QPoint const &point) const;

private:
    void uniteCorners();
    void uniteSmoothFigure();
    void uniteCornersWithEdges();
    QList<QPair<int, bool> > findCycle(QList<QPair<int, bool> > const &polygon);
    bool contains(QList<QPair<int, bool> > const &polygon, int i) const;
    int neighbourPos(const SquarePos &pos, int diagramNum) const;
    void analyzeBitmap();
    void initComponent(int x, int y);
    bool isMergedDiagrams(int i, int j,
        bool isBeginDiagram1, bool isBeginDiagram2);

    Component *mCurrentDiagram;
    Bitmap *mBitmap;
    QList<Component> mAllComponents;
};
