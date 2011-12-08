#pragma once
#include "geometricForms.h"
#include <QList>

class Diagram : public QList<SquarePos>
{
public:
    Diagram();
    void insertPos(SquarePos const & pos);
    int ID();
    void setID(int id);

private:
    bool isNeighbours(SquarePos const & pos1, SquarePos const & pos2);
    int mID;
};
