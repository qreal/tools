#pragma once
#include <QList>
#include <QPoint>
#include <QPair>

typedef QList<QPoint> PointVector;

typedef QList<PointVector> PathVector;

typedef QPair<int, int> SquarePos;

typedef QList<SquarePos> Diagram;

const int gridHeight = 50;
const int gridWidth = 50;
