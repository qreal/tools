#include "bitmap.h"
#include "stdlib.h"
#include <QDebug>

Bitmap::Bitmap(PathVector const & diagram)
{
    mDiagram = diagram;
    setUpper();
    setLower();
    setLeft();
    setRight();
    mGridHeight = height() / hStep;
    mGridWidth = width() / wStep;
    mBitmap = new int*[mGridWidth];
    for (int i = 0; i < mGridWidth; i ++)
    {
        mBitmap[i] = new int[mGridHeight];
    }
    rasterizeDiagram();
    initComponents();
}

void Bitmap::setUpper()
{
    if (mDiagram.isEmpty())
        return;
    mUpper = mDiagram.at(0).at(0).y();
    foreach (PointVector path, mDiagram)
    {
        foreach (QPoint pnt, path)
            if (pnt.y() < mUpper)
                mUpper = pnt.y();
    }
}

void Bitmap::setLower()
{
    if (mDiagram.isEmpty())
        return;
    mLower = mDiagram.at(0).at(0).y();
    foreach (PointVector path, mDiagram)
    {
        foreach (QPoint pnt, path)
            if (pnt.y() > mLower)
                mLower = pnt.y();
    }
}

void Bitmap::setLeft()
{
    if (mDiagram.isEmpty())
        return;
    mLeft = mDiagram.at(0).at(0).x();
    foreach (PointVector path, mDiagram)
    {
        foreach (QPoint pnt, path)
            if (pnt.x() < mLeft)
                mLeft = pnt.x();
    }
}

void Bitmap::setRight()
{
    if (mDiagram.isEmpty())
        return;
    mRight = mDiagram.at(0).at(0).x();
    foreach (PointVector path, mDiagram)
    {
        foreach (QPoint pnt, path)
            if (pnt.x() > mRight)
                mRight = pnt.x();
    }
}

void Bitmap::rasterizeDiagram()
{
    qDebug() << "rasterizeDiagram";
    for (int i = 0; i < mGridHeight; i++)
    {
        for (int j = 0; j < mGridWidth; j++)
            mBitmap[j][i] = 0;
    }
    foreach (PointVector path, mDiagram)
    {
        bool firstPoint = true;
        int x1 = 0;
        int y1 = 0;
        int x2 = 0;
        int y2 = 0;
        foreach (QPoint point, path)
        {
            if (mLower - mUpper == 0)
            {
                x2 = (point.x() - mLeft) * mGridWidth / (mRight - mLeft);
                y2 = 0;
            }
            else if (mRight - mLeft == 0)
            {
                x2 = 0;
                y2 = (point.y() - mUpper) * mGridHeight / (mLower - mUpper);
            }
            else
            {
                x2 = (int)((point.x() - mLeft) * mGridWidth / (mRight - mLeft));
                y2 = (int)((point.y() - mUpper) * mGridHeight / (mLower - mUpper));
            }
            if (x2 == mGridWidth)
                x2 --;
            if (y2 == mGridHeight)
                y2 --;
            if (!firstPoint)
                rasterizeSegment(x1, y1, x2, y2);
            firstPoint = false;
            x1 = x2;
            y1 = y2;
        }
    }
}

void Bitmap::rasterizeSegment(int x1, int y1, int x2, int y2)
{
    mBitmap[x1][y1] = -1;
    int x = x1;
    int y = y1;
    int deltaX = abs(x2 - x);
    int deltaY = abs(y2 - y);
    int signX = sign(x2 - x);
    int signY = sign(y2 - y);
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
        mBitmap[x][y] = -1;
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

int Bitmap::sign(int a)
{
    if (a < 0)
        return -1;
    else if (a > 0)
        return 1;
    else return 0;
}

void Bitmap::initComponents()
{
    int componentNumber = 1;
    for (int i = 0; i < mGridWidth; i ++)
    {
        for (int j = 0; j < mGridHeight; j++)
            if (initComponents(i, j, componentNumber))
                componentNumber ++;
    }
}

bool Bitmap::initComponents(int x, int y, int componentNumber)
{
    if (mBitmap[x][y] != -1)
        return true;
    mBitmap[x][y] = componentNumber;
    int cornerX = -1;
    int cornerY = -1;
    for (int i = 0; i < 4; i ++) {
        int nextCornerX = - cornerY;
        int nextCornerY = cornerX;
        int x1 = x + cornerX;
        int y1 = y + cornerY;
        int x2 = x + nextCornerX;
        int y2 = y + nextCornerY;
        if (x1 >= 0 && y1 >= 0 && x2 >= 0 && y2 >= 0
            && x1 < mGridWidth && y1 < mGridHeight && x2 < mGridWidth && y2 < mGridHeight
            && mBitmap[x1][y1] != 0 && mBitmap[x2][y2] != 0) {
            qDebug() << x << y << "corners" << x1 << y1 << x2 << y2;
            return false;
        }
        cornerX = nextCornerX;
        cornerY = nextCornerY;
    }
    if ((y == 0 || mBitmap[x][y - 1] == 0) &&
        (y == mGridHeight - 1 || mBitmap[x][y + 1] == 0) &&
        (x == 0 || mBitmap[x - 1][y] == 0) &&
        (x == mGridWidth - 1 || mBitmap[x + 1][y] ==0)) {
        //TODO:: new method
        for (int i = std::max(0, y - 1); i <= std::min(mGridHeight - 1, y + 1); i ++) {
            for (int j = std::max(0, x - 1); j <= std::min(mGridWidth - 1, x + 1); j ++)
                initComponents(j, i, componentNumber);
        }
        return true;
    }
    int neighbourX = 0;
    int neighbourY = 1;
    for (int i = 0; i < 4; i ++) {
        int nextNeighbourX = - neighbourY;
        int nextNeighbourY = neighbourX;
        if (x + neighbourX >= 0 && y + neighbourY >= 0 &&
            x + neighbourX < mGridWidth && y + neighbourY < mGridHeight &&
            x + nextNeighbourX >= 0 && y + nextNeighbourY >= 0 &&
            x + nextNeighbourX < mGridWidth && y + nextNeighbourY < mGridHeight &&
            mBitmap[x + neighbourX][y + neighbourY] != 0 && mBitmap[x + nextNeighbourX][y + nextNeighbourY] != 0) {
            int x1 = x + neighbourX - neighbourY;
            int y1 = y + neighbourX + neighbourY;
            int x2 = x - neighbourX;
            int y2 = y - neighbourY;
            int x3 = x - neighbourX + neighbourY;
            int y3 = y - neighbourX - neighbourY;
            int x4 = x + neighbourY;
            int y4 = y - neighbourX;
            if ((x1 >= 0 && x1 < mGridWidth && y1 >= 0 && y1 < mGridHeight && mBitmap[x1][y1] != 0) ||
                (x2 >= 0 && x2 < mGridWidth && y2 >= 0 && y2 < mGridHeight && mBitmap[x2][y2] != 0) ||
                (x3 >= 0 && x3 < mGridWidth && y3 >= 0 && y3 < mGridHeight && mBitmap[x3][y3] != 0) ||
                (x4 >= 0 && x4 < mGridWidth && y4 >= 0 && y4 < mGridHeight && mBitmap[x4][y4] != 0)) {
                return false;
            }

        }
        neighbourX = nextNeighbourX;
        neighbourY = nextNeighbourY;
    }
    for (int i = std::max(0, y - 1); i <= std::min(mGridHeight - 1, y + 1); i ++) {
        for (int j = std::max(0, x - 1); j <= std::min(mGridWidth - 1, x + 1); j ++)
            initComponents(j, i, componentNumber);
    }
    return true;
}

int Bitmap::height()
{
    return mLower - mUpper;
}

int Bitmap::width()
{
    return mRight - mLeft;
}

int Bitmap::xLeft()
{
    return mLeft;
}

int Bitmap::yUpper()
{
    return mUpper;
}

Diagram Bitmap::getRasterizedDiagram()
{
    Diagram diagram;
    for (int i = 0; i < mGridWidth; i ++)
    {
        for (int j = 0; j < mGridHeight; j ++)
        {
            if (mBitmap[i][j] != 0)
            {
                diagram.push_back(SquarePos(i, j));
            }
        }
    }
    return diagram;
}

Diagram Bitmap::getComponent(QPoint const & point)
{
    Diagram diagram;
    if (point.x() < mLeft || point.x() > mRight
        || point.y() < mUpper || point.y() > mLower) {
        return diagram;
    }
    int x = (point.x() - mLeft) / hStep;
    int y = (point.y() - mUpper) / hStep;
    int component = mBitmap[x][y];
    if (component == 0)
        return diagram;
    for (int i = 0; i < mGridWidth; i ++)
    {
        for (int j = 0; j < mGridHeight; j ++)
        {
            if (mBitmap[i][j] == component)
            {
                diagram.push_back(SquarePos(i, j));
            }
        }
    }
    return diagram;
}

QList<Diagram> Bitmap::getAllComponents()
{
    QMap<int, Diagram> components;
    for (int i = 0; i < mGridWidth; i ++) {
        for (int j = 0; j < mGridHeight; j ++) {
            int currentComponentNum = mBitmap[i][j];
            if (components.contains(currentComponentNum)) {
                components[currentComponentNum].push_back(SquarePos(i, j));
            }
            else if (currentComponentNum != 0) {
                Diagram newComponent;
                newComponent.push_back(SquarePos(i, j));
                components.insert(currentComponentNum, newComponent);
            }
        }
    }
    return components.values();
}
