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

	connect(this, SIGNAL(print(PathVector, Bitmap *, FormSegmentator *)), printedDiagram, SLOT(draw(PathVector, Bitmap *, FormSegmentator *)));

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
	mDiagram.clear();
	mRecognized = false;
	mComponentPoint.setX(-10000);
	mComponentPoint.setY(-10000);
	emit print(mDiagram, mBitmap, mFormSegmentator);
}

void mainWindow::recognizeImage()
{
	QString fileName = QFileDialog::QFileDialog::getOpenFileName(this,
																 tr("Recognize image"), ".",
																 tr("Png files (*.png)"));
	inputImage = new QGraphicsPixmapItem(QPixmap::fromImage(QImage(fileName)));
	mBitmap = new Bitmap(QImage(fileName));
	mBitmap2 = new Bitmap(QImage(fileName));
	recognizeDiagram();

}

void mainWindow::recognize()
{
	mBitmap = new Bitmap(mDiagram);
	mBitmap2 = new Bitmap(mDiagram);
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
	emit print(mDiagram, mBitmap, mFormSegmentator);

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
//	case 2:
//		b=10;
//		break;
//	case 3:
//		b=11;
//		break;
	case 4:
		showRecStage();
		break;
	}

}

void mainWindow::showInput()
{
	clearScene();
	inputImage->setVisible(true);
	emit print(mDiagram, mBitmap, mFormSegmentator);
}

void mainWindow::showRecStage()
{
	clearScene();
	printedDiagram->setVisible(true);
}

void mainWindow::showBitmap()
{/*
	scene->clear();
	//scene->addWidget(printedDiagram);
	//emit clear();
	QPainter painter(ui->outputView);
	painter.begin(ui->outputView);
	painter.isActive()
	QPen pen(QColor(100,100,100));
	pen.setWidth(1);
	painter.setPen(QColor(100,100,100));
	painter.setBrush(QColor(100,100,100));
	for(int i = 0; i<10; i++)
		for(int j = 0; j<5; j++)
		{
			painter.drawPoint(i,j);
		}*/

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
