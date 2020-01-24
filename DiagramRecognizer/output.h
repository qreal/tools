#pragma once

#include "component.h"
#include <QMouseEvent>
#include "bitmap.h"
#include "formSegmentator.h"
#include <QWidget>
#include <QTime>

class Output : public QWidget
{
	Q_OBJECT

public:
	explicit Output(QWidget *parent = 0);

public slots:
	void draw(PathVector RecognizedDiagram, Bitmap * newBitmap, FormSegmentator *newFormSegmentator, int stageNum);

protected:
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *paintEvent);

private:
	void drawDiagram(Component const &diagram, QColor const &color,
					 QPainter *painter);

	int randInt(int low, int high);
	PathVector mDiagram;
	Bitmap * mBitmap;
	int stage;
	bool mLeftButtonPressed;
	bool mRecognized;
	FormSegmentator *mFormSegmentator;
	QPoint mComponentPoint;
};
