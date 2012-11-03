#pragma once
#include "geometricForms.h"
#include "component.h"
#include "QImage"

class Bitmap : public QList<QList<int> >
{
public:
	Bitmap(PathVector const & diagram);
	Bitmap(QImage const & image);
	int width() const;
	int height()const;
	int xLeft() const;
	int xRight() const;
	int yUpper() const;
	int yLower() const;
	Component rasterizedDiagram() const;

private:
	void rasterizeDiagram();
	void rasterizeSegment(int x1, int y1, int x2, int y2);
	void setLower();
	void setUpper();
	void setRight();
	void setLeft();
	int sign(int a) const;

	int mLower;
	int mUpper;
	int mRight;
	int mLeft;
	PathVector mDiagram;
	int mGridHeight;
	int mGridWidth;
};

