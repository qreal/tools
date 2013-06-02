#include "diagramRecognizer.h"
#include "bitmap.h"
#include "formSegmentator.h"
#include "simpleFormsInitializer.h"
#include "recognizers/mixedGesturesManager.h"
#include "output.h"
#include "field.h"

#include <QPainter>
#include <QRect>
#include <QFileDialog>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

DiagramRecognizer::DiagramRecognizer(QWidget *parent) :
	QWidget(parent)
{
	QPushButton *clearButton = new QPushButton(tr("Clear"));
	clearButton->setFont(QFont("Times", 18, QFont::Bold));
	QPushButton *recognizeButton = new QPushButton(tr("Recognize"));
	recognizeButton->setFont(QFont("Times", 18, QFont::Bold));
	QPushButton *recognizeImageButton = new QPushButton(tr("Recognize Image"));
	recognizeImageButton->setFont(QFont("Times", 18, QFont::Bold));

	Output *PrintedDiagram = new Output;

	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(recognizeButton, SIGNAL(clicked()), this, SLOT(recognize()));
	connect(recognizeImageButton, SIGNAL(clicked()), this, SLOT(recognizeImage()));

	connect(this, SIGNAL(print(PathVector, Bitmap *, FormSegmentator *)), PrintedDiagram, SLOT(draw(PathVector, Bitmap *, FormSegmentator *)));

	QGridLayout *gridLayout = new QGridLayout;
	gridLayout->addWidget(clearButton, 0, 0);
	gridLayout->addWidget(recognizeButton, 1, 0);
	gridLayout->addWidget(recognizeImageButton, 2, 0);
	gridLayout->addWidget(PrintedDiagram, 1, 1, 3, 1);
	gridLayout->setColumnStretch(1, 10);
	setLayout(gridLayout);

	mRecognized = false;
	mComponentPoint.setX(-1000);
	mComponentPoint.setY(-1000);
	mGesturesManager = new MixedGesturesManager();
	mAbstractRecognizer = new AbstractRecognizer(mGesturesManager,
												 SimpleFormsInitializer::initialForms());
}

void DiagramRecognizer::clear()//чистит все
{
	mDiagram.clear();
	mRecognized = false;
	mComponentPoint.setX(-10000);
	mComponentPoint.setY(-10000);
	emit print(mDiagram, mBitmap, mFormSegmentator);
}

void DiagramRecognizer::recognizeImage()
{
	QString fileName = QFileDialog::QFileDialog::getOpenFileName(this,
																 tr("Recognize image"), ".",
																 tr("Png files (*.png)"));
	mBitmap = new Bitmap(QImage(fileName));
	recognizeDiagram();

}

void DiagramRecognizer::recognize()
{
	mBitmap = new Bitmap(mDiagram);
	recognizeDiagram();
}

void DiagramRecognizer::recognizeDiagram()
{
	//mRecognized = true;
	mFormSegmentator = new FormSegmentator(mBitmap);
	mFormSegmentator->uniteComponents();

	QList<Component> objects = mFormSegmentator->getObjects();
	QList < Component *> *objs = new QList < Component *>();
	foreach (Component obj, objects)
	{
		Component *newComp = new Component(obj);
		objs->push_back(newComp);
	}
	Field f(objs);
	mDiagram.clear();
	foreach (Component *object, *objs) {
		PathVector recognizedObject = mAbstractRecognizer->recognizeObject(
					(*object).figure(mBitmap->xLeft(), mBitmap->yUpper()));
		mDiagram.append(recognizedObject);
	}
	/*foreach (Component const &edge, mFormSegmentator->getEdges()) {
		mDiagram.append(edge.figure(mBitmap->xLeft(), mBitmap->yUpper()));
	}*/
	foreach (ELink *edge, *(f.getLinks()))
	{
		Component *comp = edge->getComponent();
		mDiagram.append((*comp).figure(mBitmap->xLeft(), mBitmap->yUpper()));
	}
	delete objs;
	emit print(mDiagram, mBitmap, mFormSegmentator);
}

