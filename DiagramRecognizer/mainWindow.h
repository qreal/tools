#pragma once

#include <QMainWindow>
#include "bitmap.h"
#include "formsegmentator.h"
#include "abstractRecognizer.h"
#include "output.h"

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
	void showInput();
signals:
	void print(PathVector mDiagram, Bitmap * mBitmap, FormSegmentator *mFormSegmentator);

private:
	Output *printedDiagram;
	Ui::mainWindow *ui;
	void recognizeDiagram();
	PathVector mDiagram;
	Bitmap * mBitmap;
	FormSegmentator *mFormSegmentator;
	bool mRecognized;
	QPoint mComponentPoint;
	GesturesManager *mGesturesManager;
	AbstractRecognizer *mAbstractRecognizer;
};
