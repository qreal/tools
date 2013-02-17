#include "mainWindow.h"
#include "ui_mainWindow.h"

#include "bitmap.h"
#include "formSegmentator.h"
#include "simpleFormsInitializer.h"
#include "recognizers/mixedGesturesManager.h"
#include "output.h"

#include <QPainter>
#include <QRect>
#include <QFileDialog>
#include <QApplication>
#include <QFont>
#include <QGridLayout>
#include <QPushButton>

mainWindow::mainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::mainWindow)
{
	ui->setupUi(this);

	printedDiagram = new Output;
	scene = new QGraphicsScene;
	ui->outputView->setScene(scene);
	ui->outputView->setFrameStyle(0);
	ui->outputView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
	ui->outputView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->outputView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->stages->setCurrentIndex(4);

	connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(ui->recButton, SIGNAL(clicked()), this, SLOT(recognize()));
	connect(ui->recImButton, SIGNAL(clicked()), this, SLOT(recognizeImage()));
	connect(ui->stages, SIGNAL(activated(int)), this, SLOT(showStage(int)));

	connect(this, SIGNAL(print(PathVector, Bitmap *, FormSegmentator *, int)), printedDiagram, SLOT(draw(PathVector, Bitmap *, FormSegmentator *, int)));

	mRecognized = false;
	mComponentPoint.setX(-1000);
	mComponentPoint.setY(-1000);
	mGesturesManager = new MixedGesturesManager();
	mAbstractRecognizer = new AbstractRecognizer(mGesturesManager,
												 SimpleFormsInitializer::initialForms());

	this->showFullScreen();
}

void mainWindow::clear()
{
	clearScene();
	mRecognized = false;
	mComponentPoint.setX(-10000);
	mComponentPoint.setY(-10000);
	emit print(mDiagram, mBitmap, mFormSegmentator, 4);
}

void mainWindow::recognizeImage()
{
	QString fileName = QFileDialog::QFileDialog::getOpenFileName(this,
																 tr("Recognize image"), ".",
																 tr("Png files (*.png)"));
	inputImage = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(fileName)));
	mBitmap = new Bitmap(QImage(fileName));
	recognizeDiagram();

}

void mainWindow::recognize()
{
	mBitmap = new Bitmap(mDiagram);
	recognizeDiagram();
}

void mainWindow::recognizeDiagram()
{
	//mRecognized = true;
	mFormSegmentator = new FormSegmentator(mBitmap);
	mFormSegmentator->uniteComponents();
	QList<Component> objects = mFormSegmentator->getObjects();
	mDiagram.clear();
	foreach (Component const &object, objects) {
		PathVector recognizedObject = mAbstractRecognizer->recognizeObject(
					object.figure(mBitmap->xLeft(), mBitmap->yUpper()));
		mDiagram.append(recognizedObject);
	}
	foreach (Component const &edge, mFormSegmentator->getEdges()) {
		mDiagram.append(edge.figure(mBitmap->xLeft(), mBitmap->yUpper()));
	}
	emit print(mDiagram, mBitmap, mFormSegmentator, 4);

	scene->addItem(inputImage);
	scene->addWidget(printedDiagram);
	clearScene();
	showInput();
}

void mainWindow::showStage(int index)
{
	switch(index)
	{
	case 0:
		showInput();
		break;
	case 1:
		showBitmap();
		break;
	case 2:
		showComponents();
		break;
	case 3:
		showUniStage();
		break;
	}

}

void mainWindow::showInput()
{
	clearScene();
	inputImage->setVisible(true);
}

void mainWindow::showUniStage()
{
	clearScene();
	emit print(mDiagram, mBitmap, mFormSegmentator, 4);
	printedDiagram->setVisible(true);
}

void mainWindow::showBitmap()
{
	clearScene();
	emit print(mDiagram, mBitmap, mFormSegmentator, 2);
	printedDiagram->setVisible(true);
}

void mainWindow::showComponents()
{
	clearScene();
	emit print(mDiagram, mBitmap, mFormSegmentator, 3);
	printedDiagram->setVisible(true);
}

void mainWindow::clearScene()
{
	if(inputImage->isVisible())
		inputImage->setVisible(false);
	if(printedDiagram->isVisible())
		printedDiagram->setVisible(false);
}

mainWindow::~mainWindow()
{
	delete ui;
}
