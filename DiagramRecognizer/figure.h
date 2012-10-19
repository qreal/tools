#pragma once

class Figure : public Component
{
public:
    Figure(abstractRec...);  //recognize figure, declear its type
    int getType() const;
    void setType(int value);

private:
    int type;
};
