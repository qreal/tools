#pragma once

#include "item.h"
#include "math.h"

namespace GestEditor {

/// Class, which represents the ellipse-figure
class Ellipse : public Item

{

public:
	/// Constructor
	/// @param x1 coordinate x for first point of rectangle, where ellipse is written
	/// @param y1 coordinate y for first point of rectangle, where ellipse is written
	/// @param x2 coordinate x for second point of rectangle, where ellipse is written
	/// @param y2 coordinate y for second point of rectangle, where ellipse is written
	Ellipse(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0);

	virtual void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void drawScalingRects(QPainter* painter);
	virtual void changeDragState(qreal x, qreal y);
	virtual void updateScalingRects(QPointF topLeft, QPointF bottomRight);
	virtual void transformToIdeal();
	virtual void updatePorts();
	virtual bool isIdeal() const;
	virtual QList<QPoint> getCurve(QPoint topLeftPoint);
	virtual QDomElement generateItem(QDomDocument &document);

private:

	virtual void connectPoints(QPointF oldPoint, QPointF newPoint);
	virtual void drawIdeal(QPainter *painter);

	/// Ports of ellipse are situated on it's vertices
	/// Counts ports & docking points coordinates
	/// Add ports & docking points
	void findPortRectsAndPoints();

	QRectF mLeftBottomScalRect;
	QRectF mLeftTopScalRect;
	QRectF mRightTopScalRect;
	QRectF mRightBottomScalRect;
};

}
