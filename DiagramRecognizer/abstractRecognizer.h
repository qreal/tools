#pragma once
#include <QString>
#include <QMap>
#include <QWidget>
#include <QMouseEvent>
#include "geometricForms.h"
#include "paintmanager.h"

class GesturesManager
{
public:
	virtual void initIdealGestures(
		QMap<QString, PathVector> const & objects) = 0;
	virtual void setKey(const PathVector & path) = 0;
	virtual double maxDistance(QString const & object) const = 0;
	virtual double distance(QString const & object) const = 0;
	virtual bool isMultistroke() const = 0;
};

template <typename TKey>
		class GesturesRecognizer : public GesturesManager
{
public:
	GesturesRecognizer(){}

	double distance(QString const & item) const
	{
		TKey key = mGestures[item];
		return distance(mKey, key);
	}

	void initIdealGestures(QMap<QString, PathVector> const & objects)
	{
		foreach (QString const &object, objects.keys()) {
			TKey featureSet = key(objects[object]);
			mGestures.insert(object, featureSet);
		}
	}

	void setKey(PathVector const & path)
	{
		mKey = key(path);
	}

	virtual double maxDistance(QString const & object) const = 0;

protected:
	TKey mKey;
	virtual double distance(TKey const & key1, TKey const & key2) const = 0;
	virtual TKey key(PathVector const & path) const = 0;
	QMap<QString, TKey> mGestures;
};

class AbstractRecognizer
{
public:
	AbstractRecognizer(GesturesManager * recognizer,
		const QMap<QString, PathVector> & objects)
	{
		mGesturesManager = recognizer;
		this->mObjects = objects;
		mGesturesManager->initIdealGestures(mObjects);
	}


	QString recognizeObject()
	{
		QString recognizedObject;
		mGesturesManager->setKey(mGesture);
		mGesture.clear();
		if (mObjects.empty()) {
			return "";
		}
		double minDist = mGesturesManager->maxDistance(mObjects.keys().at(0));
		foreach (QString const &object, mObjects.keys()) {
			minDist = std::min(minDist, mGesturesManager->maxDistance(object));
			double dist = mGesturesManager->distance(object);
			if (dist < minDist) {
				minDist = dist;
				recognizedObject = object;
			}
		}
		return recognizedObject;
	}

	void mousePress(QPoint const & pnt)
	{
		QList<QPoint> path;
		path.push_back(pnt);
		mGesture.push_back(path);
	}

	void mouseMove(QPoint const & pnt)
	{
		PointVector path = mGesture.back();
		mGesture.pop_back();
		path.push_back(pnt);
		mGesture.push_back(path);
	}

	void mouseRelease(QPoint const & pnt)
	{
		mouseMove(pnt);
	}

	QList<QString> objects() const
	{
		return mObjects.keys();
	}


	PathVector gesture() const
	{
		return mGesture;
	}

	PathVector recognizeObject(PathVector const &gesture)
	{
		mGesture = gesture;
		int minX = INT_MAX;
		int minY = INT_MAX;
		int maxX = INT_MIN;
		int maxY = INT_MIN;
		foreach (PointVector const &stroke, gesture) {
			foreach (QPoint const &point, stroke) {
				minX = std::min(minX, point.x());
				minY = std::min(minY, point.y());
				maxX = std::max(maxX, point.x());
				maxY = std::max(maxY, point.y());
			}
		}

		QString object = recognizeObject();
		if (object.isEmpty()) {
			return PathVector();
		}
		PathVector obj = mObjects[object];
		//TODO:: add method
		int minX2 = INT_MAX;
		int minY2 = INT_MAX;
		int maxX2 = INT_MIN;
		int maxY2 = INT_MIN;
		foreach (PointVector const &stroke, obj) {
			foreach (QPoint const &point, stroke) {
				minX2 = std::min(minX2, point.x());
				minY2 = std::min(minY2, point.y());
				maxX2 = std::max(maxX2, point.x());
				maxY2 = std::max(maxY2, point.y());
			}
		}
		for (int i = 0; i < obj.size(); i ++) {
			for (int j = 0; j < obj.at(i).size(); j ++) {
				obj[i][j] = QPoint((obj.at(i).at(j).x() - minX2) * (maxX - minX) 
				/ (maxX2 - minX2) +  minX, (obj.at(i).at(j).y() - minY2) 
				*(maxY - minY) / (maxY2 - minY2) + minY);
			}
		}
		return obj;
	}

	QMap<QString, PathVector> allGestures() const
	{
		return mObjects;
	}

private:
	GesturesManager * mGesturesManager;
	QMap<QString, PathVector> mObjects;
	PathVector mGesture;
};

