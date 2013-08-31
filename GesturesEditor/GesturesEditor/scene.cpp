#include "scene.h"

using namespace GestEditor;

static const double delta = 0.01;

Scene::Scene(QGraphicsView *view)
{
	mItemType = none;
	mGraphicsItem = NULL;
	mLastAdded = NULL;
	mView = view;
}

void Scene::drawLine()
{
	mItemType = line;
	stateSelection();
}

void Scene::drawRect()
{
	mItemType = rectangle;
	stateSelection();
}

void Scene::drawEllipse()
{
	mItemType = ellipse;
	stateSelection();
}

void Scene::drawCurve()
{
	mItemType = curve;
	stateSelection();
}

void Scene::addNone()
{
	mItemType = none;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mousePressEvent(event);
	stateSelection();
	stateMove();
	if (event->button() == Qt::LeftButton) { // avoiding double click problem
		int x1 = event->scenePos().x();
		int y1 = event->scenePos().y();
		switch (mItemType) {
		case ellipse:
			mEllipse = new Ellipse(x1, y1, x1 + delta, y1 + delta);
			addItem(this->mEllipse);
			mLastAdded = mEllipse;
			break;
		case rectangle:
			mRect = new Rectangle(x1, y1, x1 + delta, y1 + delta);
			addItem(this->mRect);
			mLastAdded = mRect;
			break;
		case line:
			mLine = new Line(x1, y1, x1 + delta, y1 + delta);
			addItem(mLine);
			mLastAdded = mLine;
			break;
		case curve:
			mCurve = new Curve(x1, y1, x1 + delta, y1 + delta);
			addItem(mCurve);
			mLastAdded = mCurve;
			break;
		case none:
			stateSelection();
			mGraphicsItem = dynamic_cast<Item *>(this->itemAt(event->scenePos(), QTransform()));
			break;
		}
		updateGraphicsItem();
		forPressResize(event);
		invalidate();
	}
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseMoveEvent(event);
	switch (mItemType) {
	case ellipse:
		reshapeEllipse(event);
		break;
	case rectangle:
		reshapeRect(event);
		break;
	case line:
		reshapeLine(event);
		break;
	case curve:
		reshapeCurve(event);
	default:
		break;
	}
	updateGraphicsItem();
	reshapeItem(event);
	invalidate();
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	QGraphicsScene::mouseReleaseEvent(event);
	switch (mItemType) {
	case ellipse:
		reshapeEllipse(event);
		break;
	case rectangle:
		reshapeRect(event);
		break;
	case line:
		reshapeLine(event);
		break;
	case curve:
		reshapeCurve(event);
		break;
	default:
		break;
	}

	reshapeItem(event);

	if (mLastAdded != NULL) {
		mLastAdded->updateScalingRects(mLastAdded->sceneBoundingRect().topLeft(), mLastAdded->sceneBoundingRect().bottomRight());
		mLastAdded->updatePorts();
	}

	emitResetButtons();
	uniteFigures();
	performIdealTransform();
	updateSceneState();

	invalidate();
}

void Scene::emitResetButtons()
{
	emit resetHighlightAllButtons();
	mItemType = none;
}

void Scene::updateGraphicsItem()
{
	if (mGraphicsItem != NULL) {
		mLastAdded = mGraphicsItem;
		mGraphicsItem->updateScalingRects(
					mGraphicsItem->sceneBoundingRect().topLeft(), mGraphicsItem->sceneBoundingRect().bottomRight());
		mGraphicsItem->updatePorts();
	}
}

void Scene::reshapeLine(QGraphicsSceneMouseEvent *event) {
	mLine->setX2andY2(event->scenePos().x(), event->scenePos().y());
	invalidate();
}

void Scene::reshapeRect(QGraphicsSceneMouseEvent *event) {
	mRect->setX2andY2(event->scenePos().x(), event->scenePos().y());
	invalidate();
}

void Scene::reshapeEllipse(QGraphicsSceneMouseEvent *event) {
	mEllipse->setX2andY2(event->scenePos().x(), event->scenePos().y());
	invalidate();
}

void Scene::reshapeCurve(QGraphicsSceneMouseEvent *event)
{
	mCurve->setX2andY2(event->scenePos().x(), event->scenePos().y());
	invalidate();
}

void Scene::forPressResize(QGraphicsSceneMouseEvent *event)
{
	if (mGraphicsItem != NULL) {
		mGraphicsItem->changeDragState(event->scenePos().x(), event->scenePos().y());
	}
}

void Scene::reshapeItem(QGraphicsSceneMouseEvent *event)
{
	if (mGraphicsItem != NULL) {
		mGraphicsItem->setOrientation();
		mGraphicsItem->resizeItem(event);
	}
}

void Scene::stateMove()
{
	if (mItemType != none) {
		foreach (QGraphicsItem *item, this->items()) {
			item->setFlag(QGraphicsItem::ItemIsMovable, false);
		}
	} else {
		foreach (QGraphicsItem *item, this->items()) {
			item->setFlag(QGraphicsItem::ItemIsMovable, true);
		}
	}
}

void Scene::stateSelection()
{
	if (mItemType != none) {
		foreach (QGraphicsItem *item, this->items()) {
			item->setFlag(QGraphicsItem::ItemIsSelectable, false);
		}
		mGraphicsItem = NULL;
	} else {
		foreach (QGraphicsItem *item, this->items()) {
			item->setFlag(QGraphicsItem::ItemIsSelectable, true);
		}
	}
}

void Scene::refresh()
{
	foreach (QGraphicsItem *item, this->items()) {
		removeItem(item);
	}
}

void Scene::deleteSelectedItem()
{
	if (mGraphicsItem != NULL) {
		this->removeItem(mGraphicsItem);
	}
}

void Scene::performIdealTransform()
{
	if (mLastAdded != NULL) {
		mLastAdded->transformToIdeal();
	}
}

void Scene::uniteFigures()
{
	foreach (QGraphicsItem *item, this->items()) {
		Item *current = dynamic_cast<Item *>(item);
		if (mLastAdded != current && mLastAdded != NULL) {
			current->intersectPorts(mLastAdded);
			current->updatePorts();
			mLastAdded->updatePorts();
		}
	}
}

void Scene::findConnectedPorts()
{
	mConnectedPorts.clear();
	foreach (QGraphicsItem *item1, this->items()) {
		Item *current1 = dynamic_cast<Item *>(item1);
		foreach (QGraphicsItem *item2, this->items()) {
			Item *current2 = dynamic_cast<Item *>(item2);
			if (current1 != current2) {
				updateConnectedPorts(&current1->mDockingPoints, &current2->mDockingPoints);
			}
		}
	}
}

void Scene::updateConnectedPorts(QVector<QPointF> *points1, QVector<QPointF> *points2)
{
	foreach(QPointF const &point1, *points1) {
		foreach (QPointF const &point2, *points2) {
			if (point1 == point2 && !mConnectedPorts.contains(point1)) {
				mConnectedPorts << point1;
			}
		}
	}
}

void Scene::drawPorts()
{
	findConnectedPorts();
	foreach (QGraphicsItem *item1, this->items()) {
		Item *current1 = dynamic_cast<Item *>(item1);
		QVector<QPointF> pointsForCurItem;
		foreach (QPointF connectPort, mConnectedPorts) {
			QPointF pointIn = current1->mapFromScene(connectPort);
			if (current1->contains(pointIn)) {
				pointsForCurItem << connectPort;
			}
		}
		current1->insertConnectedPorts(pointsForCurItem);
	}
}

void Scene::setLastAdded(Item *item)
{
	mLastAdded = item;
}

void Scene::centerView()
{
	if (mLastAdded != NULL) {
		mView->centerOn(mLastAdded);
	}
	updateSceneState();
}

void Scene::updateSceneState()
{
	foreach (QGraphicsItem *item, this->items()) {
		Item *current = dynamic_cast<Item *>(item);
		current->updateScalingRects(
				current->sceneBoundingRect().topLeft(), current->sceneBoundingRect().bottomRight());
		current->updatePorts();
	}
	uniteFigures();
	drawPorts();
}


