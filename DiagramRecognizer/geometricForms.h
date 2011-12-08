#pragma once
#include <QList>
#include <QPoint>
#include <QPair>

typedef QList<QPoint> PointVector;

typedef QList<PointVector> PathVector;

typedef QPair<int, int> SquarePos;

const int hStep = 5;
const int wStep = 5;
