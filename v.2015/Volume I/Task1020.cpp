// Topic: arithmetic
// Subtopic: elementary
// Idea: let d - denomination of minimal note, then number of tickets
//       should be between (s - d) / t + 1 and s / t

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = 3.1415926;

int main() {
	int n;
	double r, length, *x, *y;
	cin >> n >> r;
	x = new double[n + 1];
	y = new double[n + 1];
	for (int i = 0; i < n; i++) {
		cin >> x[i] >> y[i];
	}
	x[n] = x[0];
	y[n] = y[0];
	length = 2 * PI * r;
	for (int i = 0; i < n; i++) {
		length += sqrt((x[i] - x[i + 1]) * (x[i] - x[i + 1]) +
                 (y[i] - y[i + 1]) * (y[i] - y[i + 1]));
	}
	cout << setprecision(2) << fixed << length;
}
