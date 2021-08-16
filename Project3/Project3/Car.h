#pragma once
#include "DynamicObject.h"
class Car :
    public DynamicObject
{
public:
    Car(int id, std::string name, int x, int y) :DynamicObject(id, name, x, y) {};
    void printPosition() override;
    void move(Position) override;
};

