#include "BaseObject.h"

BaseObject::BaseObject(int id, std::string name, int x, int y) {
	this->id = id;
	this->name = name;
	this->position.x = x;
	this->position.y = y;
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
