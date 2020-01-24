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
	SquarePos(int x, int y)
	{
		first = x;
		second = y;
	}

	SquarePos(SquarePos const & pos)
	{
		first = pos.first;
		second = pos.second;
	}

	int first;
	int second;

	int dist(SquarePos const & pos) const
	{
		return std::max(abs(first - pos.first), abs(second - pos.second));
	}

	int length() const
	{
		return first*first + second*second;
	}

	int distP1(SquarePos const & pos) const
	{
		return abs(first - pos.first) + abs(second - pos.second);
	}

	bool operator == (SquarePos const & pos) const
	{
		return pos.first == first && pos.second == second;
	}

	bool operator != (SquarePos const pos) const
	{
		return ! operator == (pos);
	}

	bool operator < (SquarePos const & pos) const
	{
		if (first < pos.first) { return true; }
		else if (first > pos.first) { return false; }
		else
		{
			if (second < pos.second) { return true; }
			else { return false; }
		}
	}

	bool operator > (SquarePos const & pos) const
	{
		return !((operator ==(pos)) && (operator <(pos)));
	}
	SquarePos operator +(SquarePos pos) const
	{
		return SquarePos(first + pos.first, second + pos.second);
	}
	SquarePos operator -(SquarePos pos) const
	{
		return SquarePos(first - pos.first, second - pos.second);
	}
	SquarePos operator =(SquarePos pos)
	{
		first = pos.first;
		second = pos.second;
	}
};

typedef QList<SquarePos> Key;

int const hStep = 1;
int const wStep = 1;
int const neighbourhoodRad = 10;
