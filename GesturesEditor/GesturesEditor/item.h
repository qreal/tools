#pragma once

#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QVector>
#include <QtCore/QDebug>
#include <QtGui/QPainter>
#include <QtXml/QDomElement>
#include <QtCore/QList>
#include <QtCore/QPoint>
#include <QtWidgets/QGraphicsItem>
#include <QtWidgets/QGraphicsSceneMouseEvent>

namespace GestEditor {

const int scalingDrift = 12;
const int scalingRect = 8;
const int partOfIdeal = 8;
const int partForPort = 10;
const int portLengthDraw = 8;

/// Parent class for all elementary figures
class Item : public QGraphicsItem
{

public:

	/// Constructor
	/// @param x1 coordinate x for first point
	/// @param y1 coordinate y for first point
	/// @param x2 coordinate x for second point
	/// @param y2 coordinate y for second point
	Item(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = 0);

	/// Sets mX1 mY1
	/// @param x coordinate x for mX1
	/// @param y coordinate y for mY1
	void setX1andY1(qreal x, qreal y);

	/// Sets mX2 mY2
	/// @param x coordinate x for mX2
	/// @param y coordinate y for mY2
	void setX2andY2(qreal x, qreal y);

	/// Sets mX1 mY2
	/// @param x coordinate x for mX1
	/// @param y coordinate y for mY2
	void setX1andY2(qreal x, qreal y);

	/// Sets mX2 mY1
	/// @param x coordinate x for mX2
	/// @param y coordinate y for mY1
	void setX2andY1(qreal x, qreal y);

	/// Determinines how item-figure was drawn
	/// With a help of two points choose right value in Orientation enum
	/// Set this value in mOrient
	void setOrientation();

	/// Gets point which is build from mX1 mY1 coordinates
	QPointF getX1Y1() const;

	/// Gets point which is build from mX2 mY2 coordinates
	QPointF getX2Y2() const;

	/// Gets point which is build from mX1 mY2 coordinates
	QPointF getX1Y2() const;

	/// Gets point which is build from mX2 mY1 coordinates
	QPointF getX2Y1() const;

	/// Set Pen and call methods for drawing everything, which is connected with current Item
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget = 0);

	/// Draw current Item-figure
	virtual void drawItem(QPainter *painter, const QStyleOptionGraphicsItem* option, QWidget *widget = 0) = 0;

	/// Get coordinates of corners of boundingRect in scene coordinates, after move or resize
	/// Update coordinates of small rectangles, which are used for scaling
	/// @param topLeft top left point of item's bounding rectangle in scene coordinates
	/// @param bottomRoght bottom right point of item's bounding rectangle in scene coordinates
	virtual void updateScalingRects(QPointF topLeft, QPointF bottomRight) = 0;

	/// Draw rectangles, which is used for item-figure resize
	virtual void drawScalingRects(QPainter *painter) = 0;

	/// Checks is item-figure is similar to ideal
	/// If true - performs transformation to Ideal item-figure
	virtual void transformToIdeal() = 0;

	/// Update areas for ports(mDockingPoints, mDockigRects), after move or resize
	virtual void updatePorts() = 0;

	/// Check if item-figure is Ideal or not
	virtual bool isIdeal() const = 0;

	/// Checks that user clicked in a rectangle for scaling
	/// If true - update mDragState to show drag mode, choosing value from  DragState enum
	/// @param x coordinate x of clicked point
	/// @param y coordinate y of clicked point
	virtual void changeDragState(qreal x, qreal y) = 0;

	/// Gets item-figure as amount of points, which are used in Recogniser
	/// @param topLeftPoint Point which was made of the most "left" coordinate of all items on a scene and the most "high"
	/// @return List of points which describes a figure\return
	virtual QList<QPoint> getCurve(QPoint topLeftPoint) = 0;

	/// Choose between resizing and moving item
	/// @param *event event with information about mouse actions
	virtual void resizeItem(QGraphicsSceneMouseEvent *event);

	/// Determine and update appropriate point while resizing
	/// @param event event with information about mouse actions
	virtual void calcResizeItem(QGraphicsSceneMouseEvent *event);

	/// Set rectangle, which restricts area of figure
	virtual QRectF boundingRect() const;

	/// Intersect ports of two items
	/// If intersecting area is not empty - start method to connect points
	/// @param connectingItem item with whose ports current item's ports are intersecting
	virtual void intersectPorts(Item *connectingItem);

	/// Write information about item's coordinates in DomDocument
	/// @param dom document with information about item
	virtual void setXandY(QDomElement& dom);

	/// Include in mConnectedPorts the points, which are connected
	/// @param points vector of docking points, which have been connected
	void insertConnectedPorts(QVector<QPointF> points);

	/// Write information about figure's type in DomDocument
	/// @param domcument document with information about item
	virtual QDomElement generateItem(QDomDocument &document);

	/// Get figures type
	QString getName() const;

	QVector<QPointF> mConnectedPorts;
	QVector<QRectF> mDockingRects;
	QVector<QPointF> mDockingPoints;

protected:

	/// We set orientation with a help of two points, while drawing.
	/// "LeftBottomRightTop" : first point is in a Left Bottom position, second in a Right Top position
	/// if mX1 > mX2 - the first point is "Left". if mY1 > mY2 - the first point if "Top"
	enum Orientation {
		LeftBottomRightTop
		,LeftTopRightBottom
		,RightBottomLeftTop
		,RightTopLeftBottom
	};

	/// Shows in what scaling rectangle user had clicked
	enum DragState {
		None
		, TopLeft
		, TopRight
		, BottomLeft
		, BottomRight
	};

	/// Old port point should be replaced
	/// Modifies coordinates of figure, because docking should be done
	/// @param oldPoint point that is docking
	/// @param newPoint point, which represents a place of docking
	virtual void connectPoints(QPointF oldPoint, QPointF newPoint) = 0;

	/// Draws ideal figure of this item-figure
	virtual void drawIdeal(QPainter *painter) = 0;

	/// Finds value (for e.g. when figure if good for ideal transformation)
	/// According to the height&width of figure and percentage
	/// @param part percantage, which matches requirement
	/// @return int value which represents percentage of figure item size
	virtual int countRatio(int part) const;

	/// Draws circles on connected points
	void drawPorts(QPainter *painter);

	/// Finds difference between widhth and height of figure
	/// @return int difference in pixels
	int sizePolicy() const;

	/// Build rectangles which representes visible area of item
	/// @return rectangle of item for users
	virtual QRectF rectForDraw() const;

	/// Comparing docking poins of items
	/// If finds those which are close enough - connects them
	/// @param connectingItem item, which provides pointes for comparison
	void findDocPoint(Item *connectingItem);

	/// Draws rectangles which representes visible area of item
	void drawRect(QPainter *painter) const;

	/// Determine are points close enough or not
	/// @param firstPoint first point-member of comparison
	/// @param secondPoint second point-member of comparison
	bool closeEnough(QPointF firstPoint, QPointF secondPoint) const;

	QString mItemType;
	Orientation mOrient;
	DragState mDragState;
	QPen mPenforRect;
	QPen mPenForIdeal;
	QPen mPen;
	QPen mPenForPort;
	QBrush mBrush;
	qreal mX1;
	qreal mY1;
	qreal mX2;
	qreal mY2;
};

}
