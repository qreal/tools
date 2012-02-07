#pragma once
#include "geometricForms.h"
#include "diagram.h"

class Bitmap : public QList<QList<int> >
{
public:
    Bitmap(PathVector const & diagram);
    int width();
    int height();
    int xLeft();
    int xRight();
    int yUpper();
    int yLower();
    Diagram getRasterizedDiagram();

private:
    void rasterizeDiagram();
    void rasterizeSegment(int x1, int y1, int x2, int y2);
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
    int mGridHeight;
    int mGridWidth;
};

