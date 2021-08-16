#include "Tree.h"

void Tree::printPosition() {
	std::cout << "The tree'position is ";
	BaseObject::printPosition();
}

void Tree::move(Position newPosition) {
	std::cout << "Tree can not move\n";
}