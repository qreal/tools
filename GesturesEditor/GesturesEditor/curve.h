#pragma once

#include "item.h"
#include "math.h"

namespace GestEditor {

/// Class, which represents the quarter of ellipse
class Curve : public Item
{

public:
	/// Constructor
	/// @param x1 coordinate x for first point of rectangle, where curve is written
	/// @param y1 coordinate y for first point of rectangle, where curve is written
	/// @param x2 coordinate x for second point of rectangle, where curve is written
	/// @param y2 coordinate y for second point of rectangle, where curve is written
	Curve(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0);

	virtual void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void drawScalingRects(QPainter *painter);
	virtual void updateScalingRects(QPointF topLeft, QPointF bottomRight);
	virtual void resizeItem(QGraphicsSceneMouseEvent *event);
	virtual void changeDragState(qreal x, qreal y);
	virtual void transformToIdeal();
	virtual void updatePorts();
	virtual QList<QPoint> getCurve(QPoint topLeftPoint);
	virtual bool isIdeal() const;

	/// Sets span angle for curve
	/// @param spanAngle span angle
	void setSpanAngle(int spanAngle);

	/// Sets start angle for curve
	/// @param startAngle start angle
	void setStartAngle(int startAngle);
	virtual QDomElement generateItem(QDomDocument &document);

private:

	virtual void drawIdeal(QPainter *painter);
	virtual void connectPoints(QPointF oldPoint, QPointF newPoint);
	virtual void setXandY(QDomElement& dom);

	/// drawArc() draws a quarter of ellipse, which is written in the boundingRect
	/// We're increasing rectForDraw, to get a curve, which starts and ends in user clicked places
	/// @param rectangle for curve drawing
	QRectF helpRectForDraw();
	QRectF mLeftScalRect;
	QRectF mRightScalRect;
	int mStartAngle;
	int mSpanAngle;

};

}

