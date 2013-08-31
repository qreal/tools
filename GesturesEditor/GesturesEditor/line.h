#pragma once

#include "item.h"

namespace GestEditor {

/// Class, which represents the line-figure
class Line : public Item
{

public:
	Line(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0);

	virtual void drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	virtual void drawScalingRects(QPainter *painter);
	virtual void updateScalingRects(QPointF topLeft, QPointF bottomRight);
	virtual void resizeItem(QGraphicsSceneMouseEvent *event);
	virtual void changeDragState(qreal x, qreal y);
	virtual void transformToIdeal();
	virtual void updatePorts();
	virtual bool isIdeal() const;
	virtual QList<QPoint> getCurve(QPoint topLeftPoint);
	virtual QDomElement generateItem(QDomDocument &document);

private:
	virtual void connectPoints(QPointF oldPoint, QPointF newPoint);
	virtual void drawIdeal(QPainter *painter);\
	virtual void setXandY(QDomElement& dom);

	QRectF mLeftScalRect;
	QRectF mRightScalRect;
};

}


