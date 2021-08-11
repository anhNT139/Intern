#include<iostream>
#include<string>
using namespace std;

void factorial(int n) {
	if (n >= 0) {
		unsigned long long res = 1;
		for (int i = 2; i <= n; i++) {
			res *= i;
		}
		cout << "Factorial of " << n << " = " << res;
	}
	else {
		cout << "Not exist factorial of " << n;
	}
}

bool isNumber(string s) {
	for (int i = 0; i < s.size(); i++) {
		if (!isdigit(s[i]))
			return false;
	}
	return true;
}

int main() {
	string s;
	int n;
	cout << "Enter a positive integer: ";
	while (!(cin >> s) || !isNumber(s) || (n = stoi(s)) == 0) {
		cout << "Not a positive integer, please enter again: ";
	}
	factorial(n);
}