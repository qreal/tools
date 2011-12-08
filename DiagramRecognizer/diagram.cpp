#include "diagram.h"
#include "stdlib.h"

Diagram::Diagram()
{
    mID = 0;
}

int Diagram::ID()
{
    return mID;
}

void Diagram::setID(int id)
{
    mID = id;
}

void Diagram::insertPos(const SquarePos &pos)
{
    for (int i = 0; i < this->size() - 1; i ++) {
        if (isNeighbours(pos, at(i)) && isNeighbours(pos, at(i + 1))) {
            insert(i + 1, pos);
        }
    }
    if (isNeighbours(at(0), pos)) {
        push_front(pos);
    }
    push_back(pos);
}

bool Diagram::isNeighbours(const SquarePos &pos1, const SquarePos &pos2)
{
    return abs(pos1.first - pos2.first) <= 1 && abs(pos1.second - pos2.second) <= 1;
}
