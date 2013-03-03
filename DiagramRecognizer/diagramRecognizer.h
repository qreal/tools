#pragma once
#include "bitmap.h"
#include "formSegmentator.h"
#include "abstractRecognizer.h"
#include <QApplication>


class DiagramRecognizer : public QWidget
{
	Q_OBJECT

public:
	explicit DiagramRecognizer(QWidget *parent = 0);

public slots:
	void clear();
	void recognize();
	void recognizeImage();
signals:
	void print(PathVector mDiagram, Bitmap * mBitmap, FormSegmentator *mFormSegmentator);

private:
	void recognizeDiagram();
	PathVector mDiagram;
	Bitmap * mBitmap;
	FormSegmentator *mFormSegmentator;
	bool mRecognized;
	QPoint mComponentPoint;
	GesturesManager *mGesturesManager;
	AbstractRecognizer *mAbstractRecognizer;
};
