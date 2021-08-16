#pragma once
#include "DynamicObject.h"
class MotorBike :
    public DynamicObject
{
public:
    MotorBike(int id, std::string name, int x, int y) :DynamicObject(id, name, x, y) {};
    void printPosition() override;
    void move(Position) override;
};

