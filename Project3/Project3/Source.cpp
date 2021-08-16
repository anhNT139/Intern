#include<vector>
#include "Car.h"
#include "MotorBike.h"
#include "Tree.h"
#include "House.h"
using namespace std;
int main() {
	vector<BaseObject*> listObj;
	BaseObject* car = new Car(1, "car", 4, 5);
	BaseObject* motorbike = new MotorBike(2, "motorbike", 5, 6);
	BaseObject* tree = new Tree(3, "tree", 6, 7);
	BaseObject* house = new House(4, "house", 7, 8);
	listObj.push_back(car);
	listObj.push_back(motorbike);
	listObj.push_back(tree);
	listObj.push_back(house);

	cout << "Current position: \n";
	for (auto o : listObj) {
		o->printPosition();
	}
	cout << endl;
	for (int i = 0; i < listObj.size(); i++) {
		listObj[i]->move(Position(i + 10, i + 11));
	}
	for (auto o : listObj) {
		delete o;
	}
	listObj.clear();
}