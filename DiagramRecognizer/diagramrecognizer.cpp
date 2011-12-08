#include "diagramrecognizer.h"
#include "ui_diagramrecognizer.h"
#include "bitmap.h"
#include "formsegmentator.h"
#include <QMouseEvent>
#include <QPainter>
#include <QRect>
#include <QDebug>

DiagramRecognizer::DiagramRecognizer(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::DiagramRecognizer)
{
    ui->setupUi(this);
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui->recognizeButton, SIGNAL(clicked()), this, SLOT(recognize()));
    mRecognized = false;
    mLeftButtonPressed = false;
    mComponentPoint.setX(-1000);
    mComponentPoint.setY(-1000);
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
    foreach(QList<QPoint> scetch, mDiagram)
    {
        for (int i = 1; i < scetch.size(); i ++)
            painter.drawLine(scetch.at(i - 1), scetch.at(i));
    }
    if (!mRecognized)
        return;
    painter.setPen(Qt::green);
    int xLeft = mBitmap->xLeft();
    int yUpper = mBitmap->yUpper();
    int width = mBitmap->width();
    int height = mBitmap->height();
    painter.drawRect(xLeft, yUpper, width, height);
    Diagram diagram = mBitmap->getRasterizedDiagram();
    painter.setBrush(Qt::green);
    //TODO::addMethod
    foreach (SquarePos pos, diagram)
    {
        QRect rect(xLeft + pos.first * wStep,
                   yUpper + pos.second * hStep,
                   wStep, hStep);
        painter.drawRect(rect);
    }
    FormSegmentator segmentator(mBitmap);
    QList<Diagram> components = segmentator.getAllComponents();
    int size = components.size();
    for (int i = 0; i < size; i ++) {
        //TODO:: do something with colors. They are to close
        QColor color(255 * (i + 1) / size, 255 * (size - i - 1) / size,
                     255 * (i + 1) / size);
        Diagram component = components.at(i);
        drawDiagram(component, color, &painter);
    }
    Diagram curComponent = segmentator.getComponent(mComponentPoint);
    drawDiagram(curComponent, Qt::black, &painter);
    painter.setPen(Qt::black);
    for (int i = 1; i < height / hStep; i++)
    {
        painter.drawLine(xLeft, yUpper + i * hStep, xLeft + width,
                         yUpper + i * hStep);
    }
    for (int j = 1 ; j < width / wStep; j++)
    {
        painter.drawLine(xLeft + j * wStep, yUpper,
                         xLeft + j * wStep, yUpper + height);
    }
}

void DiagramRecognizer::recognize()
{
    mBitmap = new Bitmap(mDiagram);
    mRecognized = true;
    update();
}

void DiagramRecognizer::drawDiagram(const Diagram &component, const QColor &color, QPainter *painter)
{
    int xLeft = mBitmap->xLeft();
    int yUpper = mBitmap->yUpper();
    painter->setPen(color);
    painter->setBrush(color);
    foreach (SquarePos pos, component)
    {
        QRect rect(xLeft + pos.first * wStep,
                   yUpper + pos.second * hStep,
                   wStep, hStep);
        painter->drawRect(rect);
    }
}
