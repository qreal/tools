#include "bitmap.h"
#include "stdlib.h"
#include "QColor"

Bitmap::Bitmap(PathVector const & diagram)
{
    mDiagram = diagram;
    setUpper();
    setLower();
    setLeft();
    setRight();
    mGridHeight = height() / hStep + 1;
    mGridWidth = width() / wStep + 1;
    for (int i = 0; i < mGridWidth; i ++) {
        QList<int> column;
        for (int j = 0; j < mGridHeight; j ++) {
            column.push_back(0);
        }
        push_back(column);
    }
    rasterizeDiagram();
}

Bitmap::Bitmap(const QImage &image)
{
    mUpper = 0;
    mLeft = 0;
    mRight = image.width() - 1;
    mLower = image.height() - 1;
    mGridHeight = height() / hStep + 1;
    mGridWidth = width() / wStep + 1;
    for (int i = 0; i < mGridWidth; i ++) {
        QList<int> column;
        for (int j = 0; j < mGridHeight; j ++) {
            //we lose some pixels on the right side?
            int color = 0;
            for (int k = i * wStep; k < (i + 1) * wStep; k ++) {
                for (int g = j * hStep; g < (j + 1) * hStep; g ++) {
                    if (image.valid(k, g) && image.pixel(k, g) != QColor(Qt::white).rgb())
                    {
                        color = -1;
                    }
                }
            }
            column.push_back(color);
        }
        push_back(column);
    }
}

void Bitmap::setUpper()
{
    if (mDiagram.isEmpty()) {
        return;
    }
    mUpper = mDiagram.at(0).at(0).y();
    foreach (PointVector const &path, mDiagram) {
        foreach (QPoint const &pnt, path) {
            if (pnt.y() < mUpper) {
                mUpper = pnt.y();
            }
        }
    }
}

void Bitmap::setLower()
{
    if (mDiagram.isEmpty()) {
        return;
    }
    mLower = mDiagram.at(0).at(0).y();
    foreach (PointVector const &path, mDiagram) {
        foreach (QPoint const &pnt, path) {
            if (pnt.y() > mLower) {
                mLower = pnt.y();
            }
        }
    }
}

void Bitmap::setLeft()
{
    if (mDiagram.isEmpty()) {
        return;
    }
    mLeft = mDiagram.at(0).at(0).x();
    foreach (PointVector const &path, mDiagram) {
        foreach (QPoint const &pnt, path) {
            if (pnt.x() < mLeft) {
                mLeft = pnt.x();
            }
        }
    }
}

void Bitmap::setRight()
{
    if (mDiagram.isEmpty()) {
        return;
    }
    mRight = mDiagram.at(0).at(0).x();
    foreach (PointVector const &path, mDiagram) {
        foreach (QPoint const &pnt, path) {
            if (pnt.x() > mRight) {
                mRight = pnt.x();
            }
        }
    }
}

void Bitmap::rasterizeDiagram()
{
    for (int i = 0; i < mGridHeight; i++) {
        for (int j = 0; j < mGridWidth; j++) {
            operator[] (j)[i] = 0;
        }
    }
    foreach (PointVector const &path, mDiagram) {
        bool firstPoint = true;
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        foreach (QPoint const &point, path) {
            if (mLower - mUpper == 0) {
                x2 = (point.x() - mLeft) * mGridWidth / (mRight - mLeft);
                y2 = 0;
            }
            else if (mRight - mLeft == 0) {
                x2 = 0;
                y2 = (point.y() - mUpper) * mGridHeight / (mLower - mUpper);
            }
            else {
                x2 = (int)((point.x() - mLeft) * mGridWidth / (mRight - mLeft));
                y2 = (int)((point.y() - mUpper) * mGridHeight / (mLower - mUpper));
            }
            if (x2 == mGridWidth) {
                x2 --;
            }
            if (y2 == mGridHeight) {
                y2 --;
            }
            if (!firstPoint) {
                rasterizeSegment(x1, y1, x2, y2);
            }
            firstPoint = false;
            x1 = x2;
            y1 = y2;
        }
    }
}

void Bitmap::rasterizeSegment(int x1, int y1, int x2, int y2)
{
    operator [](x1)[y1] = -1;
    int x = x1;
    int y = y1;
    int deltaX = abs(x2 - x);
    int deltaY = abs(y2 - y);
    int signX = sign(x2 - x);
    int signY = sign(y2 - y);
    bool isChanged = false;
    if (deltaY > deltaX) {
        int c = deltaX;
        deltaX = deltaY;
        deltaY = c;
        isChanged = true;
    }
    int e = 2 * deltaY - deltaX;
    for (int i = 0; i < deltaX; i ++) {
        operator[](x)[y] = -1;
        while (e >= 0) {
            if (isChanged) {
                x += signX;
            }
            else {
                y +=signY;
            }
            e -= 2 * deltaX;
        }
        if (isChanged) {
            y += signY;
        }
        else {
            x += signX;
        }
        e += 2 * deltaY;
    }
}

int Bitmap::sign(int a) const
{
    if (a < 0) {
        return -1;
    }
    else if (a > 0) {
        return 1;
    }
    return 0;
}


int Bitmap::height() const
{
    return mLower - mUpper + 1;
}

int Bitmap::width() const
{
    return mRight - mLeft + 1;
}

int Bitmap::xLeft() const
{
    return mLeft;
}

int Bitmap::xRight() const
{
    return mRight;
}

int Bitmap::yUpper() const
{
    return mUpper;
}

int Bitmap::yLower() const
{
    return mLower;
}

Component Bitmap::rasterizedDiagram() const
{
    Component diagram;
    for (int i = 0; i < mGridWidth; i ++) {
        for (int j = 0; j < mGridHeight; j ++) {
            if (at(i)[j] != 0) {
                diagram.push_back(SquarePos(i, j));
            }
        }
    }
    return diagram;
}
