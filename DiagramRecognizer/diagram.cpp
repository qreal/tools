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
    return pos1.dist(pos2) <= 1;
}


void Diagram::analyze()
{
    if (at(0).dist(back()) <= neighbourhoodRad)
        mHasSelfIntersection = true;
    int next = 1;
    while (next < size() && abs(at(next).first - at(0).first) <= 1) {
        next ++;
    }
    if (next == size() && back().first == at(0).first) {
        int sign = (back().second - at(0).second) / abs(back().second - at(0).second);
        mDerivative1 = infDerivative * sign;
        mDerivative2 = - infDerivative * sign;
        return;
    }
    mDerivative1 = (at(next - 1).second - at(0).second) / (at(next - 1). first - at(0).first);
    int prev = size() - 2;
    while (prev >= 0 && abs(at(prev).first - back().first) <= 1) {
        prev --;
    }
    mDerivative2 = (at(prev + 1).second - back().second) / (at(prev + 1).first - back().first);
}

double Diagram::getDerivativeBack()
{
    return mDerivative1;
}

double Diagram::getDerivativeBegin()
{
    return mDerivative2;
}

//bool Diagram::checkNeighbour(const Diagram &diagram)
//{

//    if (norm(back(), diagram.at(0)) <= neighbourhoodRad) {
//        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), EndBegin));
//        return true;
//    }
//    if (norm(back(), diagram.back()) <= neighbourhoodRad) {
//        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), EndEnd));
//        return true;
//    }
//    if (norm(at(0), diagram.at(0)) <= neighbourhoodRad) {
//        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), BeginBegin));
//        return true;
//    }
//    if (norm(at(0), diagram.back()) <= neighbourhoodRad) {
//        mNeighborDiagrams.push_back(QPair<int, NeighbourhoodType>(diagram.ID(), BeginEnd));
//        return true;
//    }
//    return false;
//}
