#pragma once
#include "geometricForms.h"

class Bitmap
{
public:
    Bitmap(PathVector const & diagram);
    void print();
    void initComponents();
    int width();
    int height();
    int xLeft();
    int yUpper();
    Diagram getRasterizedDiagram();
    Diagram getComponent(QPoint const & point);
    QList<Diagram> getAllComponents();

private:
    void rasterizeDiagram();
    void rasterizeSegment(int x1, int y1, int x2, int y2);
    QList<QList<int> > mBitmap;
    int mLower;
    int mUpper;
    int mRight;
    int mLeft;
    PathVector mDiagram;
    void setLower();
    void setUpper();
    void setRight();
    void setLeft();
    int sign(int a);
    bool initComponents(int x, int y, int componentNumber);
    int mGridHeight;
    int mGridWidth;
};

