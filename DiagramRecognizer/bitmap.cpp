#include "bitmap.h"
#include "stdlib.h"
#include <QDebug>

Bitmap::Bitmap(PathVector const & diagram)
{
    mBitmap = new int*[gridWidth];
    for (int i = 0; i < gridWidth; i ++)
    {
        mBitmap[i] = new int[gridHeight];
    }
    mDiagram = diagram;
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
    setUpper();
    setLower();
    setLeft();
    setRight();
    for (int i = 0; i < gridHeight; i++)
    {
        for (int j = 0; j < gridWidth; j++)
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
                x2 = (point.x() - mLeft) * gridWidth / (mRight - mLeft);
                y2 = 0;
            }
            else if (mRight - mLeft == 0)
            {
                x2 = 0;
                y2 = (point.y() - mUpper) * gridHeight / (mLower - mUpper);
            }
            else
            {
                x2 = (int)((point.x() - mLeft) * gridWidth / (mRight - mLeft));
                y2 = (int)((point.y() - mUpper) * gridHeight / (mLower - mUpper));
            }
            if (x2 == gridWidth)
                x2 --;
            if (y2 == gridHeight)
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
    for (int i = 0; i < gridWidth; i ++)
    {
        for (int j = 0; j < gridHeight; j++)
            if (initComponents(i, j, componentNumber))
                componentNumber ++;
    }
}

bool Bitmap::initComponents(int x, int y, int componentNumber)
{
    if (mBitmap[x][y] != -1)
        return false;
    mBitmap[x][y] = componentNumber;
    int edges = 0;
    if (x > 0 && y > 0 && mBitmap[x - 1][y - 1] != 0 && mBitmap[x][y - 1] == 0)
        edges ++;
    if (x < gridWidth - 1 && y > 0 && mBitmap[x][y - 1] != 0 && mBitmap[x + 1][y - 1] == 0)
        edges ++;
    if (x < gridWidth - 1 && y > 0 && mBitmap[x + 1][y - 1] != 0 && mBitmap[x + 1][y] == 0)
        edges ++;
    if (x < gridWidth - 1 && y < gridHeight - 1 && mBitmap[x + 1][y] != 0 && mBitmap[x + 1] [y + 1] == 0)
        edges ++;
    if (x < gridWidth - 1 && y < gridHeight - 1 && mBitmap[x + 1][y + 1] != 0 && mBitmap[x][y + 1] == 0)
        edges ++;
    if (x > 0 && y < gridHeight - 1 && mBitmap[x][y + 1] != 0 && mBitmap[x - 1][y + 1] == 0)
        edges ++;
    if (x > 0 && y < gridHeight - 1 && mBitmap[x - 1][y + 1] != 0 && mBitmap[x - 1][y] == 0)
        edges ++;
    if (x > 0 && y > 0 && mBitmap[x - 1][y] != 0 && mBitmap[x - 1][y - 1] == 0)
        edges ++;
    if (edges <= 2)
    {
        for (int i = std::max(0, y - 1); i <= std::min(gridHeight - 1, y + 1); i ++)
        {
            for (int j = std::max(0, x - 1); j <= std::min(gridWidth - 1, x + 1); j ++)
                initComponents(j, i, componentNumber);
        }
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
    for (int i = 0; i < gridWidth; i ++)
    {
        for (int j = 0; j < gridHeight; j ++)
        {
            if (mBitmap[i][j] != 0)
            {
                diagram.push_back(SquarePos(i, j));
            }
        }
    }
    return diagram;
}

Diagram Bitmap::getComponent(int x, int y)
{
    Diagram diagram;
    int component = mBitmap[x][y];
    if (component == 0)
        return diagram;
    for (int i = 0; i < gridWidth; i ++)
    {
        for (int j = 0; j < gridHeight; j ++)
        {
            if (mBitmap[i][j] == component)
            {
                diagram.push_back(SquarePos(i, j));
            }
        }
    }
    return diagram;
}
