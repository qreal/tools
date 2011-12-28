#include "diagram.h"
#include "stdlib.h"
#include "QDebug"


Diagram::Diagram()
{
    mDerivative1 = 0;
    mDerivative2 = 0;
    mHasSelfIntersection = false;
    mID = mNextID;
    mNextID ++;
}

int Diagram::mNextID = 0;

int Diagram::ID() const
{
    return mID;
}

void Diagram::insertPos(const SquarePos &pos)
{
    for (int i = 0; i < this->size() - 1; i ++) {
        if (isNeighbours(pos, at(i)) && isNeighbours(pos, at(i + 1))) {
            insert(i + 1, pos);
            return;
        }
    }
    if (!empty() && isNeighbours(at(0), pos)) {
        push_front(pos);
        return;
    }
    push_back(pos);
}

//TODO:: init norm for SquarePos
bool Diagram::isNeighbours(const SquarePos &pos1, const SquarePos &pos2) const
{
    return norm(pos1, pos2) <= 1;
}


void Diagram::analyze()
{
    if (norm(at(0), back()) <= neighbourhoodRad)
        mHasSelfIntersection = true;
    //TODO:: initialize direction for ends of diagram
}

double Diagram::getDerivativeBack()
{
    return mDerivative1;
}

double Diagram::getDerivativeBegin()
{
    return mDerivative2;
}

int Diagram::norm(const SquarePos &pos1, const SquarePos &pos2) const
{
    return std::max(abs(pos1.first - pos2.first), abs(pos1.second - pos2.second));
}


bool Diagram::checkNeighbour(const Diagram &diagram)
{
    bool isNeighbour = false;
    if (norm(back(), diagram.at(0)) <= neighbourhoodRad) {
        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), EndBegin));
        isNeighbour = true;
    }
    if (norm(back(), diagram.back()) <= neighbourhoodRad) {
        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), EndEnd));
        isNeighbour = true;
    }
    if (norm(at(0), diagram.at(0)) <= neighbourhoodRad) {
        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), BeginBegin));
        isNeighbour = true;
    }
    if (norm(at(0), diagram.back()) <= neighbourhoodRad) {
        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), BeginEnd));
        isNeighbour = true;
    }
    return isNeighbour;
}

