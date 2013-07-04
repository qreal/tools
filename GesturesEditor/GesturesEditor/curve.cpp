#include "curve.h"

using namespace GestEditor;

static const double pi = 3.141592;
static const int pointsOnCurve = 16;
static const int pointsOnEllipsee = 64;

Curve::Curve(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent)
	: Item(x1, y1, x2, y2)
{
	mItemType = "curve";
	mStartAngle = 0;
	mSpanAngle = 0;
}

QRectF Curve::helpRectForDraw()
{
	int width = 0;
	int height = 0;
	QPoint topLeft;
	switch(mOrient) {
	case LeftBottomRightTop:
	{
		width = mX2 - mX1;
		height = mY2 - mY1;
		topLeft = QPoint(mX1 - width, mY1);
		width = 2 * width;
		height = 2 * height;
		break;
	}
	case LeftTopRightBottom:
	{
		width = mX2 - mX1;
		height = mY1 - mY2;
		topLeft = QPoint(mX1 - width , mY2 - height);
		width = 2 * width ;
		height = 2 * height;
		break;
	}
	case RightBottomLeftTop:
	{
		width = mX1 - mX2;
		height = mY2 - mY1;
		topLeft = QPoint(mX2, mY1);
		width = 2 * width ;
		height = 2 * height;
		break;
	}
	case RightTopLeftBottom:
	{
		width = mX1 - mX2;
		height = mY1 - mY2;
		topLeft = QPoint(mX2, mY2 - height);
		width = 2 * width ;
		height = 2 * height;
		break;
	}
	}
	return QRectF(topLeft, QSizeF(width, height));
}

void Curve::drawItem(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	setOrientation();
	// cutting quarter of an ellipse
	mSpanAngle = 90 * 16;
	switch (mOrient) {
	case LeftTopRightBottom:
		mStartAngle = 270 * 16;
		break;
	case LeftBottomRightTop:
		mStartAngle = 360 * 16;
		break;
	case RightTopLeftBottom:
		mStartAngle = 180 * 16;
		break;
	case RightBottomLeftTop:
		mStartAngle = 90 * 16;
		break;
	default :
		mStartAngle = 0 * 16;
		break;
	}
	painter->drawArc(helpRectForDraw(), mStartAngle, mSpanAngle);
}

void Curve::setSpanAngle(int spanAngle)
{
	mSpanAngle = spanAngle;
}

void Curve::setStartAngle(int startAngle)
{
	mStartAngle = startAngle;
}

bool Curve::isIdeal() const
{
	return (rectForDraw().width() == rectForDraw().height());
}

void Curve::drawIdeal(QPainter *painter)
{
	int size = (boundingRect().width() + boundingRect().height()- 4 * scalingDrift) / 2;
	int autoChange = (size / partOfIdeal) / 2;
	if (isIdeal()) {
		painter->setPen(mPenForIdeal);
		painter->drawArc(helpRectForDraw(), mStartAngle, 90 * 16);
	} else {
		if (sizePolicy() < autoChange) {
			painter->setPen(mPenForIdeal);
			painter->drawRect(rectForDraw());
		}
	}
}

void Curve::transformToIdeal()
{
	int size = (boundingRect().width() + boundingRect().height()- 4 * scalingDrift) / 2;
	int autoChange = (size / partOfIdeal) / 2; // Revealed that autocnange should be smaller ("/2")
	if (sizePolicy() < (autoChange)) {
		switch(mOrient) {
		case LeftBottomRightTop:
		{
			setX2andY2(mX1 + size, mY1 + size);
			break;
		}
		case LeftTopRightBottom:
		{
			setX2andY1(mX1 + size, mY2 + size);
			break;
		}
		case RightBottomLeftTop:
		{
			setX1andY2(mX2 + size, mY1 + size);
			break;
		}
		case RightTopLeftBottom:
		{
			setX1andY1(mX2 + size, mY2 + size);
			break;
		}
		}
	}
}

void Curve::drawScalingRects(QPainter *painter)
{
	painter->setPen(mPen);
	mBrush.setColor(Qt::black);
	painter->setBrush(mBrush);
	QRectF LeftScalRect;
	QRectF RightScalRect;
	int drift = scalingRect / 2;
	switch(mOrient) {
	case LeftBottomRightTop:
	{
		LeftScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		RightScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		break;
	}
	case LeftTopRightBottom:
	{
		LeftScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		RightScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		break;
	}
	case RightBottomLeftTop:
	{
		RightScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		LeftScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		break;
	}
	case RightTopLeftBottom:
	{
		RightScalRect = QRectF(QPoint(mX1 - drift, mY1 - drift), QPoint(mX1 + drift, mY1 + drift));
		LeftScalRect = QRectF(QPoint(mX2 - drift, mY2 - drift), QPoint(mX2 + drift, mY2 + drift));
		break;
	}
	}
	painter->drawRect(LeftScalRect);
	painter->drawRect(RightScalRect);
}

void Curve::updateScalingRects(QPointF topLeft, QPointF bottomRight)
{
	qreal X1 = topLeft.x();
	qreal Y1 = topLeft.y();
	qreal X2 = bottomRight.x();
	qreal Y2 = bottomRight.y();
	switch(mOrient) {
	case LeftBottomRightTop:
	{
		mLeftScalRect = QRectF(QPoint(X1 , Y1), QPoint(X1 + 2 * scalingDrift, Y1 + 2 * scalingDrift));
		mRightScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y2 - 2 * scalingDrift), QPoint(X2, Y2 ));
		break;
	}
	case LeftTopRightBottom:
	{
		mLeftScalRect = QRectF(QPoint(X1, Y2 - 2 * scalingDrift), QPoint(X1 + 2 * scalingDrift, Y2));
		mRightScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y1), QPoint(X2, Y1 + 2 * scalingDrift));
		break;
	}
	case RightBottomLeftTop:
	{
		mRightScalRect = QRectF(QPoint(X1, Y2 - 2 * scalingDrift), QPoint(X1 + 2 * scalingDrift, Y2));
		mLeftScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y1), QPoint(X2, Y1 + 2 * scalingDrift));
		break;
	}
	case RightTopLeftBottom:
	{
		mRightScalRect = QRectF(QPoint(X1, Y1), QPoint(X1 + 2 * scalingDrift, Y1 + 2 * scalingDrift));
		mLeftScalRect = QRectF(QPoint(X2 - 2 * scalingDrift, Y2 - 2 * scalingDrift), QPoint(X2, Y2));
		break;
	}
	}
}

void Curve::resizeItem(QGraphicsSceneMouseEvent *event)
{
	if (mDragState == TopLeft || mDragState == BottomRight) {
		Item::resizeItem(event);
	}
}

void Curve::changeDragState(qreal x, qreal y)
{
	QPoint clickPoint = QPoint(x, y);
	if (mLeftScalRect.contains(clickPoint)) {
		this->mDragState = TopLeft;
	} else if (mRightScalRect.contains(clickPoint)) {
			this->mDragState = BottomRight;
		} else {
			this->mDragState = None;
		}
}

void Curve::updatePorts()
{
	mDockingRects.clear();
	mDockingRects << mLeftScalRect;
	mDockingRects << mRightScalRect;
	mDockingPoints.clear();
	mDockingPoints << mapToScene(getX1Y1());
	mDockingPoints << mapToScene(getX2Y2());
}

void Curve::connectPoints(QPointF oldPoint, QPointF newPoint)
{
	int xDiff = oldPoint.x() - newPoint.x();
	int yDiff = oldPoint.y() - newPoint.y();
	if (oldPoint == mapToScene(getX1Y1())) {
		setX1andY1(mX1 - xDiff, mY1 - yDiff);
		// if one point is already connected, it shouldn't be disconnected
		if (!mConnectedPorts.contains(mapToScene(getX2Y2()))) {
			setX2andY2(mX2 - xDiff, mY2 - yDiff);
		}
	}
	if (oldPoint == mapToScene(getX2Y2())) {
		setX2andY2(mX2 - xDiff, mY2 - yDiff);
		// if one point is already connected, it shouldn't be disconnected
		if (!mConnectedPorts.contains(mapToScene(getX1Y1()))) {
			setX1andY1(mX1 - xDiff, mY1 - yDiff);
		}
	}
}

QDomElement Curve::generateItem(QDomDocument &document)
{
	QDomElement curve = document.createElement("curve");
	setXandY(curve);
	return curve;
}

void Curve::setXandY(QDomElement& dom)
{
	QPointF fstPointF = mapToScene(getX1Y1());
	QPointF sndPointF = mapToScene(getX2Y2());
	QPoint fstPoint = fstPointF.toPoint();
	QPoint sndPoint = sndPointF.toPoint();
	qreal x1 = fstPoint.x();
	qreal y1 = fstPoint.y();
	qreal x2 = sndPoint.x();
	qreal y2 = sndPoint.y();

	dom.setAttribute("y1", QString::number(y1));
	dom.setAttribute("x1", QString::number(x1));
	dom.setAttribute("y2", QString::number(y2));
	dom.setAttribute("x2", QString::number(x2));
}


QList<QPoint> Curve::getCurve(QPoint topLeftPoint)
{
	QPointF pointOne = mapToScene(boundingRect().topLeft());
	QPointF pointTwo = mapToScene(boundingRect().bottomRight());
	QPoint point1 = pointOne.toPoint();
	QPoint point2 = pointTwo.toPoint();
	QList<QPoint> Curve;
	QPoint centre = (point1 + point2) / 2;
	int diam = static_cast<int>(sqrt(pow(point2.x() - point1.x(), 2) + pow(point2.y() - point1.y(), 2)));
	switch (mOrient) {
	case LeftTopRightBottom:
		for (int i = (3 * pointsOnCurve); i < pointsOnEllipsee; i++)
		{
			int x = static_cast<int>(diam * cos(2 * pi * i / pointsOnEllipsee) / 2);
			int y = static_cast<int>(diam * sin(2 * pi * i / pointsOnEllipsee) / 2);
			Curve.push_back(centre + QPoint(x, y));
		}
		break;
	case LeftBottomRightTop:
		for (int i = 0; i < pointsOnCurve; i++)
		{
			int x = static_cast<int>(diam * cos(2 * pi * i / pointsOnEllipsee) / 2);
			int y = static_cast<int>(diam * sin(2 * pi * i / pointsOnEllipsee) / 2);
			Curve.push_back(centre + QPoint(x, y));
		}
		break;
	case RightTopLeftBottom:
		for (int i = (2 * pointsOnCurve); i < (3 * pointsOnCurve); i++)
		{
			int x = static_cast<int>(diam * cos(2 * pi * i / pointsOnEllipsee) / 2);
			int y = static_cast<int>(diam * sin(2 * pi * i / pointsOnEllipsee) / 2);
			Curve.push_back(centre + QPoint(x, y));
		}
	case RightBottomLeftTop:
		for (int i = pointsOnCurve; i < (2 * pointsOnCurve); i++)
		{
			int x = static_cast<int>(diam * cos(2 * pi * i / pointsOnEllipsee) / 2);
			int y = static_cast<int>(diam * sin(2 * pi * i / pointsOnEllipsee) / 2);
			Curve.push_back(centre + QPoint(x, y));
		}
		break;
	default :
		mStartAngle = 0 * 16;
		break;
	}
	Curve.push_back(QPoint(centre.x() + diam / 2, centre.y()));
	return Curve;
}

