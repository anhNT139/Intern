#pragma once
#include<iostream>
struct Position {
	int x;
	int y;
	Position() {
		x = y = 0;
	}
	Position(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
class BaseObject
{
protected:
	int id;
	std::string name;
	Position position;
public:
	explicit BaseObject(int, std::string, int, int);
	virtual std::string getName();
	virtual int getid();
	virtual void printPosition();
	virtual void move(Position) = 0;
};

