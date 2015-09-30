// Topic: peculiar
// Subtopic: data manipulation

#include <iostream>
#include "..\Tools\MVector.h"

int main() {
	int n;
	vector2<int> in;
	cin >> n;
	in.assign(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> in[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			cout << in[i - j][j] << ' ';
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j++) {
			cout << in[n - 1 - (j - i)][j] << ' ';
		}
	}
}
