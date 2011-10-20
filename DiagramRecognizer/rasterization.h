#pragma once
#include "geometricForms.h"
#include "cmath"
#include "stdlib.h"

class Rasterization
{
public:
    static Key getKey(const PathVector &mousePath)
    {
        double * bitmap = new double[gridHeight][gridWidth];
        if (mousePath.isEmpty())
            return key;
        double lower = lowerBound(mousePath);
        double upper = upperBound(mousePath);
        double right = rightBound(mousePath);
        double left = leftBound(mousePath);
        foreach (PointVector path, mousePath)
        {
            bool firstPoint = true;
            SquarePos previous;
            SquarePos last;
            foreach (QPoint point, path)
            {
                if (lower - upper == 0)
                {
                    last.first = (point.x() - left) * gridWidth / (right - left);
                    last.second = 0;
                }
                else if (right - left == 0)
                {
                    last.first = 0;
                    last.second = (point.y() - upper) * gridHeight / (lower - upper);
                }
                else
                {
                    last.first = (int)((point.x() - left) * gridWidth / (right - left));
                    last.second = (int)((point.y() - upper) * gridHeight / (lower - upper));
                }
                if (last.first == gridWidth)
                    last.first --;
                if (last.second == gridHeight)
                    last.second --;
                if (!firstPoint)
                {
                    rasterizeSegment(previous, last, &key);
                    firstPoint = false;
                }
                previous = last;
            }
        }
        return key;
    }
private:
    static int upperBound(const PathVector & mousePath)
    {
        if (mousePath.isEmpty())
            return 0;
        int upperBound = mousePath.at(0).at(0).y();
        foreach (PointVector path, mousePath)
        {
            foreach (QPoint pnt, path)
                if (pnt.y() < upperBound)
                    upperBound = pnt.y();
        }
        return upperBound;
    }
    static int lowerBound(const PathVector & mousePath)
    {
        if (mousePath.isEmpty())
            return 0;
        int lowerBound = mousePath.at(0).at(0).y();
        foreach (PointVector path, mousePath)
        {
            foreach (QPoint pnt, path)
                if (pnt.y() > lowerBound)
                    lowerBound = pnt.y();
        }
        return lowerBound;
    }
    static int leftBound(const PathVector & mousePath)
    {
        if (mousePath.isEmpty())
            return 0;
        int leftBound = mousePath.at(0).at(0).x();
        foreach (PointVector path, mousePath)
        {
            foreach (QPoint pnt, path)
                if (pnt.x() < leftBound)
                    leftBound = pnt.x();
        }
        return leftBound;
    }
    static int rightBound(const PathVector & mousePath)
    {
        if (mousePath.isEmpty())
            return 0;
        int rightBound = mousePath.at(0).at(0).x();
        foreach (PointVector path, mousePath)
        {
            foreach (QPoint pnt, path)
                if (pnt.x() > rightBound)
                    rightBound = pnt.x();
        }
        return rightBound;
    }
    static void rasterizeSegment(SquarePos const & pos1, SquarePos const & pos2, Key * segment)
    {
        if (!segment->isEmpty() && pos1 == segment->at(0))
            segment->pop_back();
        if (pos1 == pos2)
        {
            segment->push_back(pos1);
            return;
        }
        int x = pos1.first;
        int y = pos1.second;
        int deltaX = abs(pos2.first - x);
        int deltaY = abs(pos2.second - y);
        int signX = sign(pos2.first - x);
        int signY = sign(pos2.second - y);
        bool isChanged = false;
        if (deltaY > deltaX)
        {
            int c = deltaX;
            deltaX = deltaY;
            deltaY = c;
            isChanged = true;
        }
        int e = 2 * deltaY - deltaX;
        for (int i = 0; i < deltaX; i ++)
        {
            segment->push_back(SquarePos(x, y));
            while (e >= 0)
            {
                if (isChanged)
                    x += signX;
                else
                    y +=signY;
                e -= 2 * deltaX;
            }
            if (isChanged)
                y += signY;
            else
                x += signX;
            e += 2 * deltaY;
        }
    }
    static int sign(int a)
    {
        if (a < 0)
            return -1;
        else if (a > 0)
            return 1;
        else return 0;
    }
};

