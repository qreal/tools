#include "diagramrecognizer.h"
#include "ui_diagramrecognizer.h"
#include "bitmap.h"
#include "formsegmentator.h"
#include "simpleformsinitializer.h"
#include "recognizers/mixedgesturesmanager.h"
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QFileDialog>

DiagramRecognizer::DiagramRecognizer(QWidget *parent) :
		QMainWindow(parent),
		ui(new Ui::DiagramRecognizer)
{
	ui->setupUi(this);
	connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(ui->recognizeButton, SIGNAL(clicked()), this, SLOT(recognize()));
	connect(ui->recognizeImageButton, SIGNAL(clicked()), this, SLOT(recognizeImage()));
	mRecognized = false;
	mLeftButtonPressed = false;
	mComponentPoint.setX(-1000);
	mComponentPoint.setY(-1000);
	mGesturesManager = new MixedGesturesManager();
	mAbstractRecognizer = new AbstractRecognizer(mGesturesManager,
		 SimpleFormsInitializer::initialForms());
}

DiagramRecognizer::~DiagramRecognizer()
{
	delete ui;
}

void DiagramRecognizer::mouseMoveEvent(QMouseEvent * event)
{
	if (mLeftButtonPressed) {
		mDiagram.back().push_back(event->pos());
	}
	this->update();
}

void DiagramRecognizer::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
		mLeftButtonPressed = true;
		QList<QPoint> newScetch;
		newScetch.push_back(event->pos());
		mDiagram.push_back(newScetch);
	}
	else {
		mComponentPoint = event->pos();
	}
	this->update();
}

void DiagramRecognizer::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
		mLeftButtonPressed = false;
		mDiagram.back().push_back(event->pos());
	}
	this->update();
}

void DiagramRecognizer::clear()
{
	mDiagram.clear();
	mRecognized = false;
	mComponentPoint.setX(-10000);
	mComponentPoint.setY(-10000);
	this->update();
}

void DiagramRecognizer::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	foreach(PointVector const &scetch, mDiagram) {
		for (int i = 1; i < scetch.size(); i ++) {
			QPen pen(Qt::black);
			pen.setWidth(3);
			if ((scetch.at(0) - scetch.back()).manhattanLength() <= 4) {
				painter.setPen(pen);
				painter.drawLine(scetch.at(i - 1), scetch.at(i));
			}
			else
			{
				pen.setColor(Qt::red);
				painter.setPen(pen);
				painter.drawLine(scetch.at(0), scetch.back());
			}
		}
	}
	if (!mRecognized) {
		return;
	}
	int xLeft = mBitmap->xLeft();
	int yUpper = mBitmap->yUpper();
	int width = mBitmap->width();
	int height = mBitmap->height();
	QList<Diagram> components = mFormSegmentator->allComponents();
	int size = components.size();
	for (int i = 0; i < size; i ++) {
		//TODO:: do something with colors. They are to close
		QColor color(255 * (i + 1) / size, 255 * (size - i - 1) / size,
			 255 * (i + 1) / size);
		Diagram component = components.at(i);
		drawDiagram(component, color, &painter);
	}
	Diagram curComponent = mFormSegmentator->component(mComponentPoint);
	drawDiagram(curComponent, Qt::black, &painter);
	painter.setPen(Qt::black);
	for (int i = 1; i < height / hStep; i++) {
		painter.drawLine(xLeft, yUpper + i * hStep, xLeft + width,
			yUpper + i * hStep);
	}
	for (int j = 1 ; j < width / wStep; j++) {
		painter.drawLine(xLeft + j * wStep, yUpper,
			xLeft + j * wStep, yUpper + height);
	}
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
	QList<Diagram> objects = mFormSegmentator->objects();
	mDiagram.clear();
	foreach (Diagram const &object, objects) {
		PathVector recognizedObject = mAbstractRecognizer->recognizeObject(
			object.figure(mBitmap->xLeft(), mBitmap->yUpper()));
		mDiagram.append(recognizedObject);
	}
	foreach (Diagram const &edge, mFormSegmentator->edges()) {
		mDiagram.append(edge.figure(mBitmap->xLeft(), mBitmap->yUpper()));
	}
	update();
}

void DiagramRecognizer::drawDiagram(const Diagram &component, const QColor &color, QPainter *painter)
{
	int xLeft = mBitmap->xLeft();
	int yUpper = mBitmap->yUpper();
	QPen pen(color);
	pen.setWidth(4);
	painter->setPen(color);
	painter->setBrush(color);
	foreach (SquarePos const &pos, component) {
		QRect rect(xLeft + pos.first * wStep,
			yUpper + pos.second * hStep,
			wStep, hStep);
		painter->drawRect(rect);
	}
}
