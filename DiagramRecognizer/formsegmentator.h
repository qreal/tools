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
    Bitmap *mBitmap;
    void analyzeBitmap();
    bool initComponents(int x, int y, Diagram * diagram);
    void initComponents();
    QList<Diagram> mAllComponents;
};


