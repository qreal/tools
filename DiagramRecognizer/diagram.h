#pragma once
#include "geometricForms.h"
#include <QList>

class Diagram : public QList<SquarePos>
{
public:
    void insert(SquarePos const & pos)
    {
        for (int i = 0; i < this->size() - 1; i ++) {
            if (isNeighbours(pos, at(i)) && isNeighbours(pos, at(i + 1))) {
                this->insert(i + 1, pos);
            }
        }
        if (isNeighbours(at(0), pos)) {
            push_front(pos);
        }
        push_back(pos);
    }
private:
    bool isNeighbours(SquarePos const & pos1, SquarePos const & pos2) {
        return abs(pos1.first - pos2.first) <= 1 && abs(pos1.second - pos2.second) <= 1;
    }
};

