#pragma once
#include "bitmap.h"

class FormSegmentator
{
public:
    FormSegmentator(Bitmap *bimap);
    Diagram getComponent(QPoint const & point);
    QList<Diagram> getAllComponents();
    void uniteComponents();

private:
    Diagram *mCurrentDiagram;
    Bitmap *mBitmap;
    void analyzeBitmap();
    void initComponent(int x, int y);
    int componentWithNeighbour();
    Diagram merge(Diagram const & diagram1, Diagram const & diagram2, bool isBegin1, bool isBegin2);
    QList<Diagram> mAllComponents;
};


