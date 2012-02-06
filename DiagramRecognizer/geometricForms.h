#pragma once
#include "stdlib.h"
#include <QList>
#include <QPoint>
#include <QPair>

typedef QList<QPoint> PointVector;

typedef QList<PointVector> PathVector;

//typedef QPair<int, int> SquarePos;
struct SquarePos
{
public:
    SquarePos(int x, int y)
    {
        first = x;
        second = y;
    }

    int first;
    int second;
    int dist(SquarePos const & pos) const
    {
        return std::max(abs(first - pos.first), abs(second - pos.second));
    }
    bool operator == (SquarePos const & pos)
    {
        return pos.first == first && pos.second == second;
    }
};

const int hStep = 5;
const int wStep = 5;
const int neighbourhoodRad = 3;
