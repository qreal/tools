#pragma once

#include <QMainWindow>
#include "bitmap.h"
#include "formsegmentator.h"
#include "abstractRecognizer.h"
#include "output.h"
#include <QGraphicsScene>
#include <QGraphicsItem>

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit mainWindow(QWidget *parent = 0);
	~mainWindow();

public slots:
	void clear();
	void recognize();
	void recognizeImage();
	void showStage(int);
signals:
	void print(PathVector mDiagram, Bitmap * mBitmap, FormSegmentator *mFormSegmentator, int stageNum);

private:
	void showInput();
	void showUniStage();
	void showBitmap();
	void showComponents();
	void clearScene();
	QGraphicsPixmapItem *inputImage;
	Output *printedDiagram, ;
	Ui::mainWindow *ui;
	void recognizeDiagram();
	PathVector mDiagram;
	Bitmap * mBitmap, * mBitmap2;
	FormSegmentator *mFormSegmentator;
	bool mRecognized;
	QPoint mComponentPoint;
	GesturesManager *mGesturesManager;
	AbstractRecognizer *mAbstractRecognizer;
	QGraphicsScene *scene;
};
