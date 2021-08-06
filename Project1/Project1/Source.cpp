#include <iostream>
using namespace std;

void swap1(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void swap2(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int a, b;
	cin >> a >> b;
	cout << "Before swap: a = " << a << ", b = " << b << endl;
	swap2(&a, &b);
	cout << "After swap: a = " << a << ", b = " << b << endl;
}