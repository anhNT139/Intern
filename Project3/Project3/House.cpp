#include "House.h"

void House::printPosition() {
	std::cout << "The house'position is ";
	BaseObject::printPosition();
}

void House:: move(Position newPosition) {
	std::cout << "House can not move\n";
}