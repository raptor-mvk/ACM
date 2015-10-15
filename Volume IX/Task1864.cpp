// Topic: arithmetic
// Subtopic: elementary

#include <iostream>
#include <cmath>

using namespace std;

const double PAYMENT = 100.0;
const double EPS = 1e-7;

int main() {
	int n;
	double *vol, sum = 0.0, sum2 = 0.0;
	cin >> n;
	vol = new double[n];
	for (int i = 0; i < n; i++) {
		cin >> vol[i];
		sum += vol[i];
	}
	sum /= (double)(n + 1);
	for (int i = 0; i < n; i++) {
		vol[i] -= sum;
		sum2 += vol[i] > 0 ? vol[i] : 0;
	}
	for (int i = 0; i < n; i++) {
		if (vol[i] > 0) {
			cout << (int)floor(PAYMENT * vol[i] / sum2 + EPS) << ' ';
		} else {
			cout << "0 ";
		}
	}
}
