#pragma once
#include "StaticObject.h"
class House :
    public StaticObject
{
public:
    House(int id, std::string name, int x, int y) :StaticObject(id, name, x, y) {};
    void printPosition() override;
    void move(Position);
};

