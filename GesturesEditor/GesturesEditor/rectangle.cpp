#include "rectangle.h"

using namespace GestEditor;

Rectangle::Rectangle(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent) : Item(x1, y1, x2, y2)
{
	mItemType = "rectangle";
}

void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (this->isSelected()) {
		drawRect(painter);
		drawIdeal(painter);
		drawPorts(painter);
		drawScalingRects(painter);
	} else {
		painter->setPen(this->mPen);
		this->drawItem(painter, option, widget);
	}
}

void Rectangle::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawRect(rectForDraw());
}

bool Rectangle::isIdeal() const
{
	return (rectForDraw().width() == rectForDraw().height());
}

void Rectangle::drawIdeal(QPainter *painter)
{
	int size = std::min(rectForDraw().width(), rectForDraw().height());
	int autoChange = size / partOfIdeal;
	if (sizePolicy() < autoChange) {
		QRectF idealRect = QRectF(rectForDraw().topLeft(), QSize(size, size));
		painter->setPen(mPenForIdeal);
		painter->drawRect(idealRect);
	}
}

void Rectangle::transformToIdeal()
{
	int size = std::min(rectForDraw().width(), rectForDraw().height());
	int autoChange = size / partOfIdeal;
	if (sizePolicy() < autoChange) {
		switch(mOrient) {
		case LeftBottomRightTop:
			setX2andY2(mX1 + size, mY1 + size);
			break;
		case LeftTopRightBottom:
			setX2andY1(mX1 + size, mY2 + size);
			break;
		case RightBottomLeftTop:
			setX1andY2(mX2 + size, mY1 + size);
			break;
		case RightTopLeftBottom:
			setX1andY1(mX2 + size, mY2 + size);
			break;
		}
	}
}

void Rectangle::drawScalingRects(QPainter *painter) {

	painter->setPen(mPen);
	mBrush.setColor(Qt::black);
	painter->setBrush(mBrush);
	QRectF leftTopScalRect;
	QRectF leftBottomScalRect;
	QRectF rightTopScalRect;
	QRectF rightBottomScalRect;
	int drift = scalingRect / 2;

	switch(mOrient) {
	case LeftBottomRightTop:
	{
		leftTopScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		leftBottomScalRect = QRectF(QPoint(mX1  - drift, mY2 - drift), QPoint(mX1 + drift, mY2 + drift));
		rightTopScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		rightBottomScalRect = QRectF(QPoint(mX2 - drift, mY1 - drift), QPoint(mX2 + drift, mY1 + drift));
		break;
	}
	case LeftTopRightBottom:
	{
		leftTopScalRect = QRectF(QPoint(mX1 - drift, mY2 - drift), QPoint(mX1 + drift, mY2 + drift));
		leftBottomScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		rightBottomScalRect = QRectF(QPoint(mX2 - drift, mY1 - drift), QPoint(mX2 + drift, mY1 + drift));
		rightTopScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		break;
	}
	case RightBottomLeftTop:
	{
		rightTopScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		rightBottomScalRect = QRectF(QPoint(mX1 - drift, mY2 - drift), QPoint(mX1 + drift, mY2 + drift));
		leftTopScalRect = QRectF(QPoint(mX2 - drift, mY1 - drift), QPoint(mX2 + drift, mY1 + drift));
		leftBottomScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		break;
	}
	case RightTopLeftBottom:
	{
		rightBottomScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		rightTopScalRect = QRectF(QPoint(mX1 - drift, mY2 - drift), QPoint(mX1 + drift, mY2 + drift));
		leftBottomScalRect = QRectF(QPoint(mX2 - drift, mY1 - drift), QPoint(mX2 + drift, mY1 + drift));
		leftTopScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		break;
	}
	}
	painter->drawRect(leftTopScalRect);
	painter->drawRect(rightBottomScalRect);
	painter->drawRect(leftBottomScalRect);
	painter->drawRect(rightTopScalRect);
}

void Rectangle::changeDragState(qreal x, qreal y) {
	QPoint clickPoint = QPoint(x, y);
	if (mLeftTopScalRect.contains(clickPoint)) {
		mDragState = TopLeft;
	} else if (mLeftBottomScalRect.contains(clickPoint)) {
			mDragState = BottomLeft;
		} else if (mRightTopScalRect.contains(clickPoint)) {
				mDragState = TopRight;
			} else if (mRightBottomScalRect.contains(clickPoint)) {
					mDragState = BottomRight;
				} else {
					mDragState = None;
				}
}

void Rectangle::updateScalingRects(QPointF topLeft, QPointF bottomRight) {
	qreal X1 = topLeft.x();
	qreal Y1 = topLeft.y();
	qreal X2 = bottomRight.x();
	qreal Y2 = bottomRight.y();
	switch(mOrient) {
	case LeftBottomRightTop:
	{
		mLeftTopScalRect = QRectF(QPoint(X1, Y1), QPoint(X1 + 2 * scalingDrift, Y1 + 2 * scalingDrift));
		mLeftBottomScalRect = QRectF(QPoint(X1, Y2 - 2 * scalingDrift), QPoint(X1 + 2 * scalingDrift, Y2));
		mRightBottomScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y2 - 2 * scalingDrift), QPoint(X2, Y2));
		mRightTopScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y1), QPoint(X2, Y1 + 2 * scalingDrift));
		break;
	}
	case LeftTopRightBottom:
	{

		mLeftTopScalRect = QRectF(QPoint(X1, Y2 - 2 * scalingDrift), QPoint(X1 + 2 * scalingDrift, Y2));
		mLeftBottomScalRect = QRectF(QPoint(X1, Y1), QPoint(X1 + 2 * scalingDrift, Y1 + 2 * scalingDrift));
		mRightBottomScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y1), QPoint(X2 , Y1 + 2 * scalingDrift));
		mRightTopScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y2 - 2 * scalingDrift), QPoint(X2, Y2));
		break;
	}
	case RightBottomLeftTop:
	{
		mRightTopScalRect = QRectF(QPoint(X1, Y1), QPoint(X1 + 2 * scalingDrift, Y1 + 2 * scalingDrift));
		mRightBottomScalRect = QRectF(QPoint(X1, Y2 - 2 * scalingDrift), QPoint(X1 + 2 * scalingDrift, Y2));
		mLeftTopScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y1), QPoint(X2 , Y1 + 2 * scalingDrift));
		mLeftBottomScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y2 - 2 * scalingDrift), QPoint(X2, Y2));
		break;
	}
	case RightTopLeftBottom:
	{
		mRightBottomScalRect = QRectF(QPoint(X1, Y1), QPoint(X1 + 2 * scalingDrift, Y1 + 2 * scalingDrift));
		mRightTopScalRect = QRectF(QPoint(X1, Y2 - 2 * scalingDrift), QPoint(X1 + 2 * scalingDrift, Y2));
		mLeftBottomScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y1), QPoint(X2 , Y1 + 2 * scalingDrift));
		mLeftTopScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y2 - 2 * scalingDrift), QPoint(X2, Y2));
		break;
	}
	}
}

void Rectangle::updatePorts()
{
	mDockingRects.clear();
	mDockingPoints.clear();
	mDockingRects << mLeftTopScalRect;
	mDockingRects << mRightTopScalRect;
	mDockingRects << mLeftBottomScalRect;
	mDockingRects << mRightBottomScalRect;
	findPortRectsAndPoints();
	mDockingPoints << mapToScene(getX1Y1());
	mDockingPoints << mapToScene(getX2Y2());
	mDockingPoints << mapToScene(getX1Y2());
	mDockingPoints << mapToScene(getX2Y1());

}

void Rectangle::connectPoints(QPointF oldPoint, QPointF newPoint)
{
	int xDiff = oldPoint.x() - newPoint.x();
	int yDiff = oldPoint.y() - newPoint.y();
	for (int i = 0; i < mDockingPoints.size(); i++) {
		if (oldPoint == mDockingPoints[i]) {
				setX1andY1(mX1 - xDiff, mY1 - yDiff);
				setX2andY2(mX2 - xDiff, mY2 - yDiff);
		}
	}
}

void Rectangle::findPortRectsAndPoints()
{
	// bottom, top, left, right - relatively ellipse
	QRectF topMiddleRect;
	QRectF bottomMiddleRect;
	QRectF rightMiddleRect;
	QRectF leftMiddleRect;
	QPointF topMiddlePoint;
	QPointF bottomMiddlePoint;
	QPointF rightMiddlePoint;
	QPointF leftMiddlePoint;
	int drift = scalingDrift;
	int middleX;
	int middleY;

	switch(mOrient) {
	case LeftBottomRightTop:
	{
		middleX = mX1 + (mX2 - mX1) / 2;
		middleY = mY1 + (mY2 - mY1) / 2;
		topMiddlePoint = QPointF(middleX, mY1);
		bottomMiddlePoint = QPointF(middleX, mY2);
		rightMiddlePoint = QPointF(mX2, middleY);
		leftMiddlePoint =QPoint(mX1, middleY);

		topMiddleRect = QRectF(mapToScene(QPoint(middleX - drift, mY1 - drift)), mapToScene(QPoint(middleX + drift, mY1 + drift)));
		bottomMiddleRect = QRectF(mapToScene(QPoint(middleX  - drift, mY2 - drift)), mapToScene(QPoint(middleX + drift, mY2 + drift)));
		rightMiddleRect = QRectF(mapToScene(QPoint(mX2 - drift, middleY - drift)), mapToScene(QPoint(mX2 + drift, middleY + drift)));
		leftMiddleRect = QRectF(mapToScene(QPoint(mX1 - drift, middleY - drift)), mapToScene(QPoint(mX1 + drift, middleY + drift)));
		break;
	}
	case LeftTopRightBottom:
	{
		middleX = mX1 + (mX2 - mX1) / 2;
		middleY = mY2 + (mY1 - mY2) / 2;
		topMiddlePoint = QPointF(middleX, mY2);
		bottomMiddlePoint = QPointF(middleX, mY1);
		rightMiddlePoint = QPointF(mX2, middleY);
		leftMiddlePoint =QPoint(mX1, middleY);

		topMiddleRect = QRectF(mapToScene(QPoint(middleX - drift, mY2 - drift)), mapToScene(QPoint(middleX + drift, mY2 + drift)));
		bottomMiddleRect = QRectF(mapToScene(QPoint(middleX  - drift, mY1 - drift)), mapToScene(QPoint(middleX + drift, mY1 + drift)));
		rightMiddleRect = QRectF(mapToScene(QPoint(mX2 - drift, middleY - drift)), mapToScene(QPoint(mX2 + drift, middleY + drift)));
		leftMiddleRect = QRectF(mapToScene(QPoint(mX1 - drift, middleY - drift)), mapToScene(QPoint(mX1 + drift, middleY + drift)));
		break;
	}
	case RightBottomLeftTop:
	{
		middleX = mX2 + (mX1 - mX2) / 2;
		middleY = mY1 + (mY2 - mY1) / 2;
		topMiddlePoint = QPointF(middleX, mY1);
		bottomMiddlePoint = QPointF(middleX, mY2);
		rightMiddlePoint = QPointF(mX1, middleY);
		leftMiddlePoint =QPoint(mX2, middleY);

		topMiddleRect = QRectF(mapToScene(QPoint(middleX - drift, mY1 - drift)), mapToScene(QPoint(middleX + drift, mY1 + drift)));
		bottomMiddleRect = QRectF(mapToScene(QPoint(middleX  - drift, mY2 - drift)), mapToScene(QPoint(middleX + drift, mY2 + drift)));
		rightMiddleRect = QRectF(mapToScene(QPoint(mX1 - drift, middleY - drift)), mapToScene(QPoint(mX1 + drift, middleY + drift)));
		leftMiddleRect = QRectF(mapToScene(QPoint(mX2 - drift, middleY - drift)), mapToScene(QPoint(mX2 + drift, middleY + drift)));
		break;
	}
	case RightTopLeftBottom:
	{
		middleX = mX2 + (mX1 - mX2) / 2;
		middleY = mY2 + (mY1 - mY2) / 2;
		topMiddlePoint = QPointF(middleX, mY2);
		bottomMiddlePoint = QPointF(middleX, mY1);
		rightMiddlePoint = QPointF(mX1, middleY);
		leftMiddlePoint =QPoint(mX2, middleY);

		topMiddleRect = QRectF(mapToScene(QPoint(middleX - drift, mY2 - drift)), mapToScene(QPoint(middleX + drift, mY2 + drift)));
		bottomMiddleRect = QRectF(mapToScene(QPoint(middleX  - drift, mY1 - drift)), mapToScene(QPoint(middleX + drift, mY1 + drift)));
		rightMiddleRect = QRectF(mapToScene(QPoint(mX1 - drift, middleY - drift)), mapToScene(QPoint(mX1 + drift, middleY + drift)));
		leftMiddleRect = QRectF(mapToScene(QPoint(mX2 - drift, middleY - drift)), mapToScene(QPoint(mX2 + drift, middleY + drift)));
		break;
	}
	}

	mDockingRects << topMiddleRect;
	mDockingRects << bottomMiddleRect;
	mDockingRects << rightMiddleRect;
	mDockingRects << leftMiddleRect;
	mDockingPoints << mapToScene(topMiddlePoint);
	mDockingPoints << mapToScene(bottomMiddlePoint);
	mDockingPoints << mapToScene(rightMiddlePoint);
	mDockingPoints << mapToScene(leftMiddlePoint);
}

QDomElement Rectangle::generateItem(QDomDocument &document)
{
	QDomElement rectangle = document.createElement("rectangle");
	setXandY(rectangle);
	return rectangle;
}

QList<QPoint> Rectangle::getCurve(QPoint topLeftPoint)
{
	QList<QPoint> component;
	int minX = topLeftPoint.x();
	int minY = topLeftPoint.y();
	QPointF point1 = mapToScene(QPointF(mX1, mY1));
	QPointF point2 = mapToScene(QPointF(mX2, mY1));
	QPointF point3 = mapToScene(QPointF(mX2, mY2));
	QPointF point4 = mapToScene(QPointF(mX1, mY2));
	point1 = QPointF(point1.x() - minX, point1.y() - minY);
	point2 = QPointF(point2.x() - minX, point2.y() - minY);
	point3 = QPointF(point3.x() - minX, point3.y() - minY);
	point4 = QPointF(point4.x() - minX, point4.y() - minY);
	component.push_back(point1.toPoint());
	component.push_back(point2.toPoint());
	component.push_back(point3.toPoint());
	component.push_back(point4.toPoint());
	component.push_back(point1.toPoint());
	return component;
}
