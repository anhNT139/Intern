#pragma once
#include "StaticObject.h"
class Tree :
    public StaticObject
{
public:
    Tree(int id, std::string name, int x, int y) :StaticObject(id, name, x, y) {};
    void printPosition() override;
    void move(Position);
};

