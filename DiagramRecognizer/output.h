#pragma once

#include "component.h"
#include <QMouseEvent>
#include "bitmap.h"
#include "formsegmentator.h"
#include <QWidget>

 class Output : public QWidget
 {
     Q_OBJECT

 public:
     explicit Output(QWidget *parent = 0);

 public slots:
     void draw(PathVector RecognizedDiagram, Bitmap * newBitmap, FormSegmentator *newFormSegmentator);

 protected:
     void mousePressEvent(QMouseEvent *);
     void mouseReleaseEvent(QMouseEvent *);
     void mouseMoveEvent(QMouseEvent *);
     void paintEvent(QPaintEvent *paintEvent);

 private:
     void drawDiagram(Component const &diagram, QColor const &color,
         QPainter *painter);

     PathVector mDiagram;
     Bitmap * mBitmap;
     bool mLeftButtonPressed;
     bool mRecognized;
     FormSegmentator *mFormSegmentator;
     QPoint mComponentPoint;
 };
