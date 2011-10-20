#include "diagramrecognizer.h"
#include "ui_diagramrecognizer.h"
#include "bitmap.h"
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
    ui->widthBox->setMaximum(gridWidth - 1);
    ui->widthBox->setMinimum(0);
    ui->heightBox->setMaximum(gridHeight - 1);
    ui->heightBox->setMinimum(0);
    connect(ui->widthBox, SIGNAL(valueChanged(int)), this, SLOT(update()));
    connect(ui->heightBox, SIGNAL(valueChanged(int)), this, SLOT(update()));
}

DiagramRecognizer::~DiagramRecognizer()
{
    delete ui;
}

void DiagramRecognizer::mouseMoveEvent(QMouseEvent * event)
{
    mDiagram.back().push_back(event->pos());
    this->update();
}

void DiagramRecognizer::mousePressEvent(QMouseEvent * event)
{
    QList<QPoint> newScetch;
    newScetch.push_back(event->pos());
    mDiagram.push_back(newScetch);
    this->update();
}

void DiagramRecognizer::mouseReleaseEvent(QMouseEvent * event)
{
    mDiagram.back().push_back(event->pos());
    this->update();
}

void DiagramRecognizer::clear()
{
    mDiagram.clear();
    mRecognized = false;
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
        QRect rect(xLeft + pos.first * width / gridWidth,
                   yUpper + pos.second * height / gridHeight,
                   width / gridWidth, height / gridHeight);
        painter.drawRect(rect);
    }
    Diagram partDiagram = mBitmap->getComponent(ui->widthBox->value(), ui->heightBox->value());
    painter.setPen(Qt::red);
    painter.setBrush(Qt::red);
    foreach (SquarePos pos, partDiagram)
    {
        QRect rect(xLeft + pos.first * width / gridWidth,
                   yUpper + pos.second * height / gridHeight,
                   width / gridWidth, height / gridHeight);
        painter.drawRect(rect);
    }
    painter.setPen(Qt::black);
    for (int i = 1; i < gridHeight; i++)
    {
        painter.drawLine(xLeft, yUpper + i * height / gridHeight, xLeft + width,
                         yUpper + i * height / gridHeight);
    }
    for (int j = 1 ; j < gridWidth; j++)
    {
        painter.drawLine(xLeft + j * width / gridWidth, yUpper,
                         xLeft + j * width / gridWidth, yUpper + height);
    }
}

void DiagramRecognizer::recognize()
{
    mBitmap = new Bitmap(mDiagram);
    mRecognized = true;
    update();
}
