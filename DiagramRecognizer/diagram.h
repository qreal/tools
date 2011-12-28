#pragma once
#include "geometricForms.h"
#include <QList>

const int neighbourhoodRad = 3;
const double infDerivative = 1000;

class Diagram : public QList<SquarePos>
{
public:
    Diagram();
    void insertPos(SquarePos const & pos);
    void analyze();
    int ID() const;
    bool checkNeighbour(Diagram const &diagram);
    double getDerivativeBegin();
    double getDerivativeBack();

private:
    static int mNextID;
    bool isNeighbours(SquarePos const & pos1, SquarePos const & pos2) const;
    bool mHasSelfIntersection;
    int mID;
    double mDerivative1;
    double mDerivative2;
    int norm(SquarePos const & pos1, SquarePos const & pos2) const;
    enum NeighbourhoodType
    {
        BeginBegin,
        BeginEnd,
        EndBegin,
        EndEnd
    };
    //some strange structure
    QList<QPair<int, NeighbourhoodType> > mNeighborDiagrams;
};
