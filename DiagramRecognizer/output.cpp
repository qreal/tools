#include <QPainter>

#include "output.h"

Output::Output(QWidget *parent)
	: QWidget(parent)
{
	setPalette(QPalette(QColor(250, 250, 250)));
	setAutoFillBackground(true);

	mLeftButtonPressed = false;
	mRecognized = false;
}

void Output::draw(PathVector RecognizedDiagram, Bitmap *newBitmap, FormSegmentator *newFormSegmentator, int stageNum)
{
	mBitmap = newBitmap;
	mDiagram = RecognizedDiagram;
	mFormSegmentator = newFormSegmentator;
	stage = stageNum;
	this->update();
}

void Output::mouseMoveEvent(QMouseEvent * event)
{
	if (mLeftButtonPressed) {
		mDiagram.back().push_back(event->pos());
	}
	this->update();
}

void Output::mousePressEvent(QMouseEvent * event)
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

void Output::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
		mLeftButtonPressed = false;
		mDiagram.back().push_back(event->pos());
	}
	this->update();
}

void Output::paintEvent(QPaintEvent *paintEvent)
{
	QPainter painter(this);
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec()); //for random colours generation
	foreach(PointVector const &scetch, mDiagram) {
		for (int i = 1; i < scetch.size(); i ++) {
			QPen pen(Qt::black);
			if(stage == 2 || stage == 4)
				pen.setColor(Qt::black);
			else if(stage == 3)
				pen.setColor(QColor::fromRgb(randInt(0,255), randInt(0,255), randInt(0,255)));
			pen.setWidth(3);
			if ((scetch.at(0) - scetch.back()).manhattanLength() <= 4) {
				painter.setPen(pen);
				painter.drawLine(scetch.at(i - 1), scetch.at(i));
			}
			else
			{
				if(stage == 2)
					pen.setColor(Qt::black);
				else if(stage == 3)
					pen.setColor(QColor::fromRgb(randInt(0,255), randInt(0,255), randInt(0,255)));
				else if(stage == 4)
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
	QList<Component> components = mFormSegmentator->getAllComponents();
	int size = components.size();
	for (int i = 0; i < size; i ++) {
		//TODO:: do something with colors. They are to close
		QColor color(255 * (i + 1) / size, 255 * (size - i - 1) / size,
					 255 * (i + 1) / size);
		Component component = components.at(i);
		drawDiagram(component, color, &painter);
	}
	Component curComponent = mFormSegmentator->component(mComponentPoint);
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

void Output::drawDiagram(const Component &component, const QColor &color, QPainter *painter)
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

int Output::randInt(int low, int high)
{
	return qrand() % ((high + 1) - low) + low;
}
