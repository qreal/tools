#pragma once
#include "bitmap.h"

class FormSegmentator
{
public:
	FormSegmentator(Bitmap *bimap);
	Diagram component(QPoint const &point) const;
	QList<Diagram> allComponents() const;
	void uniteComponents();
	QList<Diagram> objects() const;
	QList<Diagram> edges() const;

private:
	void uniteCorners();
	void uniteSmoothFigure();
	int neighbourPos(const SquarePos &pos, int diagramNum) const;
	void analyzeBitmap();
	void initComponent(int x, int y);
	bool isMergedDiagrams(int i, int j,
		bool isBeginDiagram1, bool isBeginDiagram2);

	Diagram *mCurrentDiagram;
	Bitmap *mBitmap;
	QList<Diagram> mAllComponents;
};


