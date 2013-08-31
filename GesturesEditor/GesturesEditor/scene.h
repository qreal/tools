#pragma once

#include <QtWidgets/QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QtWidgets/QGraphicsView>

#include "line.h"
#include "rectangle.h"
#include "ellipse.h"
#include "curve.h"

namespace GestEditor {

/// Class, which provides drawing
class Scene : public QGraphicsScene
{
	Q_OBJECT

public:
	Scene(QGraphicsView *view);

	/// Sets marker, that Line button is pressed
	void drawLine();

	/// Sets marker, that Rectangle button is pressed
	void drawRect();

	/// Sets marker, that Ellipse button is pressed
	void drawEllipse();

	/// Sets marker, that Curve button is pressed
	void drawCurve();

	/// Sets marker, that there is no pressed buttom
	void addNone();

	/// Removes all item-figures from the scene
	void refresh();

	/// Removes selected item from the scene
	void deleteSelectedItem();

	/// Checks all items on a scene, do they have intersecting ports
	void uniteFigures();

	/// Writes connected points for every item on a scene
	void drawPorts();

	/// Determines last added item
	/// @param item item that was added last
	void setLastAdded(Item *item);

	/// Sets focus on last added item
	void centerView();

signals:
	///Reset all hilighted buttons
	void resetHighlightAllButtons();
private:
	/// Enum for item determination
	enum ItemTypes {
		none
		, line
		, rectangle
		, ellipse
		, curve
	};

	/// Defines behavior after mouse was pressed
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

	/// Defines behavior after mouse was released
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

	/// Defines behavior after mouse was moved
	virtual void mouseMoveEvent( QGraphicsSceneMouseEvent *event);

	/// Checks that user clicked to resize item
	virtual void forPressResize(QGraphicsSceneMouseEvent *event);

	/// Updates scaling rectangles of item
	/// Updates ports of item
	void updateGraphicsItem();

	/// Sets coordinates for line with a help of information from mouse
	/// @param event provides information about mouse actions
	void reshapeLine(QGraphicsSceneMouseEvent *event);

	/// Sets coordinates for rectangle with a help of information from mouse
	/// @param event provides information about mouse actions
	void reshapeRect(QGraphicsSceneMouseEvent *event);

	/// Sets coordinates for ellipse with a help of information from mouse
	/// @param event provides information about mouse actions
	void reshapeEllipse(QGraphicsSceneMouseEvent *event);

	/// Sets coordinates for Curve with a help of information from mouse
	/// @param event provides information about mouse actions
	void reshapeCurve(QGraphicsSceneMouseEvent *event);

	/// Updates orientation of item and calls resize method
	/// @param event provides information about mouse actions
	void reshapeItem(QGraphicsSceneMouseEvent *event);

	/// Changes property ItemIsMovable for item-figures
	void stateMove();

	/// Changes property ItemIsSelectable for item-figures
	void stateSelection();

	/// Tries to transform figures ti ideal figures
	void performIdealTransform();

	/// Takes docking points from every item to check their identity
	void findConnectedPorts();

	/// Reset hightlighted buttons
	void emitResetButtons();

	/// Tests docking points of two items for their identity
	/// If equals - updates connected points of items
	/// @points1 first list of points in comparison
	/// @points2 second list of points in comparison
	void updateConnectedPorts(QVector<QPointF> *points1, QVector<QPointF> *points2);

	/// Defines behavior after adding all items from the XML (object file) to the scene
	void updateSceneState();

	ItemTypes mItemType;
	QVector<QPointF> mConnectedPorts;
	Item *mLastAdded;
	Curve *mCurve;
	Item *mGraphicsItem;
	Line *mLine;
	Rectangle *mRect;
	Ellipse *mEllipse;
	QPen mPenForPort;
	QBrush mBrushForPort;
	QGraphicsView *mView;
};

}

