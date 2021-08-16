#pragma once
#include "BaseObject.h"
class StaticObject :
    public BaseObject
{
public:
    StaticObject(int id, std::string name, int x, int y) :BaseObject(id, name, x, y) {};
    virtual void move(Position) = 0;
};

