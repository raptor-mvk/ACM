// Topic: arithmetic
// Subtopic: elementary

#include "../Tools/Calculator.h"
#include <iostream>

int main() {
	int k,n;
	Calculator c;
	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> n;
		cout << c.getPrime(n) << '\n';
	}
}
