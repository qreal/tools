#pragma once
#include "stdlib.h"
#include <QList>
#include <QPoint>
#include <QPair>

typedef QList<QPoint> PointVector;

typedef QList<PointVector> PathVector;

typedef QList<QPoint> PointVector;

typedef QList<PointVector> PathVector;

typedef QPair<QString, PathVector> Entity;

typedef QPair<double *, double *> MixedKey;

static const int gridSize = 81;

struct SquarePos
{
public:
    SquarePos(int x, int y)//методы???инициализирует структуру точки(координат точки)
	{
		first = x;
		second = y;
	}

	int first;
	int second;

    int dist(SquarePos const & pos) const//штука считающая максимальную разницу у координат двух точек
	{
		return std::max(abs(first - pos.first), abs(second - pos.second));
	}

    int distP1(SquarePos const & pos) const//считает сумму разностей координат
	{
		return abs(first - pos.first) + abs(second - pos.second);
	}

    bool operator == (SquarePos const & pos) const//что за синтаксис? смотрит не одинаковы ли две точки
	{
		return pos.first == first && pos.second == second;
    }
};

typedef QList<SquarePos> Key;

int const hStep = 1;
int const wStep = 1;
int const neighbourhoodRad = 10;
