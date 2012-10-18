#pragma once

class Figure : public Component
{
public:
    Figure(abstractRec...);  //распознает фигуру, задает ее тип
    int getType() const;
    void setType(int value);

private:
    int type;
};
