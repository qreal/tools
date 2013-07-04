#include "item.h"

using namespace GestEditor;

Item::Item(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent) :
	QGraphicsItem(parent) {
	mX1 = x1;
	mY1 = y1;
	mX2 = x2;
	mY2 = y2;
	mPen = QPen(Qt::darkGray, 2, Qt::SolidLine, Qt::RoundCap);
	mPenForIdeal = QPen(Qt::green, 2, Qt::SolidLine, Qt::RoundCap);
	mPenforRect= QPen(Qt::lightGray, 1, Qt::DashLine, Qt::RoundCap);
	mPenForPort = QPen(Qt::blue, 2, Qt::DotLine, Qt::RoundCap);
	mBrush = QBrush(Qt::SolidPattern);
	mDragState = None;
	setOrientation();
	setFlag(QGraphicsItem::ItemIsSelectable, true);
}

QRectF Item::boundingRect() const
{
	QPoint topLeft;
	QPoint bottomRight;
	// count scalin' drift function
	switch(mOrient) {
	case LeftBottomRightTop:
	{
		topLeft = QPoint(mX1 - scalingDrift, mY1 - scalingDrift);
		bottomRight = QPoint(mX2 + scalingDrift, mY2 + scalingDrift);
		break;
	}
	case LeftTopRightBottom:
	{
		topLeft = QPoint(mX1 - scalingDrift, mY2 - scalingDrift);
		bottomRight = QPoint(mX2 + scalingDrift, mY1 + scalingDrift);
		break;
	}
	case RightBottomLeftTop:
	{
		topLeft = QPoint(mX2 - scalingDrift, mY1 - scalingDrift);
		bottomRight = QPoint(mX1 + scalingDrift, mY2 + scalingDrift);
		break;
	}
	case RightTopLeftBottom:
	{
		topLeft = QPoint(mX2 - scalingDrift, mY2 - scalingDrift);
		bottomRight = QPoint(mX1 + scalingDrift, mY1 + scalingDrift);
		break;
	}
	}
	return QRectF(topLeft, bottomRight);
}

QRectF Item::rectForDraw() const
{
	QPointF topLeft = QPointF(boundingRect().topLeft().x() + scalingDrift, boundingRect().topLeft().y() + scalingDrift);
	QPointF bottomRight = QPointF(boundingRect().bottomRight().x() - scalingDrift, boundingRect().bottomRight().y() - scalingDrift);
	return QRectF(topLeft, bottomRight);
}

void Item::setX1andY1(qreal x, qreal y)
{
	mX1 = x;
	mY1 = y;
}

void Item::setX2andY2(qreal x, qreal y)
{
	mX2 = x;
	mY2 = y;
}

void Item::setX1andY2(qreal x, qreal y)
{
	mX1 = x;
	mY2 = y;
}

void Item::setX2andY1(qreal x, qreal y)
{
	mX2 = x;
	mY1 = y;
}

void Item::paint(QPainter* painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->setPen(mPen);
	drawItem(painter, option, widget);
	drawPorts(painter);
	if (isSelected()) {
		drawRect(painter);
		drawIdeal(painter);
		drawScalingRects(painter);
	}
}

void Item::drawRect(QPainter *painter) const
{
	painter->setPen(mPenforRect);
	painter->drawRect(rectForDraw());
	qDebug() << "RectForDraw = " << rectForDraw();
	qDebug() << "BoundingRect = " << boundingRect();
}

void Item::drawPorts(QPainter *painter)
{
	mBrush.setColor(Qt::white);
	painter->setPen(mPenForPort);
	foreach(QPointF const &port, mConnectedPorts) {
		painter->drawEllipse(mapFromScene(port), portLengthDraw, portLengthDraw);
	}
}

void Item::resizeItem(QGraphicsSceneMouseEvent *event) {
	if (mDragState != None) {
		calcResizeItem(event);
	} else {
		setFlag(QGraphicsItem::ItemIsMovable, true);
	}
}

void Item::calcResizeItem(QGraphicsSceneMouseEvent *event) {
	qreal x = mapFromScene(event->scenePos()).x();
	qreal y = mapFromScene(event->scenePos()).y();
	if (mDragState != None) {
		setFlag(QGraphicsItem::ItemIsMovable, false);
	}
	switch (mDragState) {
	case TopLeft:
		setX1andY1(x,y);
		break;
	case TopRight:
		setX2andY1(x,y);
		break;
	case BottomLeft:
		setX1andY2(x,y);
		break;
	case BottomRight:
		setX2andY2(x,y);
	default:
		break;
	}
}

QPointF Item::getX1Y1() const
{
	return QPointF(mX1, mY1);
}

QPointF Item::getX2Y2() const
{
	return QPointF(mX2, mY2);
}

QPointF Item::getX1Y2() const
{
	return QPointF(mX1, mY2);
}

QPointF Item::getX2Y1() const
{
	return QPointF(mX2, mY1);
}

void Item::setOrientation() {
	if (mX1 <= mX2) {
		if (mY1 <= mY2) {
			mOrient = LeftBottomRightTop;
		} else {
			mOrient = LeftTopRightBottom;
		}
	} else {
		if (mY1 <= mY2) {
			mOrient = RightBottomLeftTop;
		} else {
			mOrient = RightTopLeftBottom;
		}
	}
}

int Item::sizePolicy() const
{
	int maxDiff = 0;
	switch(mOrient) {
	case LeftBottomRightTop:
	{
		maxDiff = std::max(mX2 - mX1, mY2 - mY1) - std::min(mX2 - mX1, mY2 - mY1);
		break;
	}
	case LeftTopRightBottom:
	{
		maxDiff = std::max(mX2 - mX1, mY1 - mY2) - std::min(mX2 - mX1, mY1 - mY2);
		break;
	}
	case RightBottomLeftTop:
	{
		maxDiff = std::max(mX1 - mX2, mY2 - mY1) - std::min(mX1 - mX2, mY2 - mY1);
		break;
	}
	case RightTopLeftBottom:
	{
		maxDiff = std::max(mX1 - mX2, mY1 - mY2) - std::min(mX1 - mX2, mY1 - mY2);
		break;
	}
	}
	return maxDiff;
}

void Item::intersectPorts(Item *connectingItem)
{
	foreach (QRectF const &docRect, connectingItem->mDockingRects) {
		foreach (QRectF const &docRect2, mDockingRects) {
			if (docRect.intersects(docRect2)) {
				findDocPoint(connectingItem);
			}
		}
	}
}

void Item::findDocPoint(Item *connectingItem)
{
	foreach (QPointF const &docPoint, mDockingPoints) {
		foreach (QPointF const &conDocPoint, connectingItem->mDockingPoints) {
			if (closeEnough(docPoint, conDocPoint)) {
				connectingItem->connectPoints(conDocPoint, docPoint);
				connectingItem->updatePorts();
			}
		}
	}
}

bool Item::closeEnough(QPointF firstPoint, QPointF secondPoint) const
{
	if ((abs(firstPoint.x() - secondPoint.x()) < countRatio(partForPort))
			&& (abs(firstPoint.y() - secondPoint.y()) < countRatio(partForPort))) {
		return true;
	} else {
		return false;
	}
}

int Item::countRatio(int part) const
{
	int size = (rectForDraw().width() + rectForDraw().height()) / 2;
	int ratio = size / part;
	return ratio;
}

void Item::insertConnectedPorts(QVector<QPointF> points)
{
	mConnectedPorts.clear();
	mConnectedPorts = points;
}

QDomElement Item::generateItem(QDomDocument &document)
{
	QDomElement dom = document.createElement("Not stated!");
	return dom;
}

void Item::setXandY(QDomElement& dom)
{
	QPointF fstPointF = mapToScene(rectForDraw().topLeft());
	QPointF sndPointF = mapToScene(rectForDraw().bottomRight());
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

QString Item::getName() const
{
	return mItemType;
}

