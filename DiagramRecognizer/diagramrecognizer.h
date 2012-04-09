#pragma once
#include "bitmap.h"
#include "formsegmentator.h"
#include "abstractRecognizer.h"
#include <QMainWindow>

namespace Ui {
	class DiagramRecognizer;
}

class DiagramRecognizer : public QMainWindow
{
	Q_OBJECT

public:
	explicit DiagramRecognizer(QWidget *parent = 0);
	~DiagramRecognizer();

protected:
	void mousePressEvent(QMouseEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	void mouseMoveEvent(QMouseEvent *);
	void paintEvent(QPaintEvent *);

private:
	void drawDiagram(Diagram const &diagram, QColor const &color,
		QPainter *painter);
	Ui::DiagramRecognizer *ui;
	PathVector mDiagram;
	Bitmap * mBitmap;
	FormSegmentator *mFormSegmentator;
	bool mRecognized;
	bool mLeftButtonPressed;
	QPoint mComponentPoint;
	GesturesManager *mGesturesManager;
	AbstractRecognizer *mAbstractRecognizer;

private slots:
	void clear();
	void recognize();
};
