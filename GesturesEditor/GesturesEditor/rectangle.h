#pragma once

#include "item.h"

namespace GestEditor {

/// Class, which represents the line-figure
class Rectangle : public Item

{

public:
	Rectangle(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0);

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void drawScalingRects(QPainter *painter);
	virtual void changeDragState(qreal x, qreal y);
	virtual void updateScalingRects(QPointF topLeft, QPointF bottomRight);
	virtual void transformToIdeal();
	virtual void updatePorts();
	virtual bool isIdeal() const;
	virtual QList<QPoint> getCurve(QPoint topLeftPoint);
	virtual QDomElement generateItem(QDomDocument &document);

protected:

private:
	virtual void drawIdeal(QPainter *painter);
	virtual void connectPoints(QPointF oldPoint, QPointF newPoint);

	/// Extra ports of rectangle are situated on it's sides middles
	/// Counts ports & docking points coordinates
	/// Adds ports & docking points
	void findPortRectsAndPoints();

	QRectF mLeftBottomScalRect;
	QRectF mLeftTopScalRect;
	QRectF mRightTopScalRect;
	QRectF mRightBottomScalRect;
};

}

