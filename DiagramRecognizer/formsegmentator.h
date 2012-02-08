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
    void initComponents();
    QList<Diagram> mAllComponents;
};


