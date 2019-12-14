// Topic: peculiar
// Subtopic: data representation

#include <iostream>
#include "../Tools/MVector.h"

int main() {
	int n, cur_number = 1;
	vector2<int> locker;
	cin >> n;
	locker.assign(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			locker[i-j][j] = cur_number++;
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j++) {
			locker[n - 1 - (j - i)][j] = cur_number++;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= 0; j--) {
			cout << locker[j][i] << ' ';
		}
		cout << '\n';
	}
}
