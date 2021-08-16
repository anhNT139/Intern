#pragma once
#include "BaseObject.h"
class DynamicObject :
    public BaseObject
{
public:
    explicit DynamicObject(int id, std::string name, int x, int y) :BaseObject(id, name, x, y) {};
    virtual void move(Position);
};

