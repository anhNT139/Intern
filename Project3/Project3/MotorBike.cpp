#include "MotorBike.h"

void MotorBike::printPosition() {
	std::cout << "The motorbike's position is ";
	BaseObject::printPosition();
}

void MotorBike::move(Position newPosition) {
	DynamicObject::move(newPosition);
	std::cout << "The motorbike has been moved to new position ";
	BaseObject::printPosition();
}