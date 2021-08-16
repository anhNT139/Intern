#include "Car.h"

void Car::printPosition() {
	std::cout << "The car's position is ";
	BaseObject::printPosition();
}

void Car::move(Position newposition) {
	DynamicObject::move(newposition);
	std::cout << "The car has been moved to new position ";
	BaseObject::printPosition();
}