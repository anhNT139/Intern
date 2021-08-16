#include "BaseObject.h"

BaseObject::BaseObject(int id, std::string name, int x, int y) {
	BaseObject::id = id;
	BaseObject::name = name;
	BaseObject::position.x = x;
	BaseObject::position.y = y;
}
std::string BaseObject::getName() {
	return name;
}

int BaseObject::getid() {
	return id;
}

void BaseObject::printPosition() {
	std::cout << "(" << position.x << ", " << position.y << ")\n";
}
