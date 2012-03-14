#pragma once
#include "bitmap.h"

class FormSegmentator
{
public:
  FormSegmentator(Bitmap *bimap);
  Diagram getComponent(QPoint const & point);
  QList<Diagram> getAllComponents();
  void uniteComponents();
  QList<Diagram> getObjects();
  QList<Diagram> getEdges();

private:
  Diagram *mCurrentDiagram;
  Bitmap *mBitmap;
  void analyzeBitmap();
  void initComponent(int x, int y);
  QList<Diagram> mAllComponents;
};


