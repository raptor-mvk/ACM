// Topic: physics
// Subtopic: free fall
// Idea: time of free fall from 'h' to 'l / 2' is
//       sqrt((2 * h - l) / G / 100)

#include <iostream>
#include <cmath>

using namespace std;

const double G = 9.81;

int main() {
	int l, h, w;
	double t;
	cin >> l >> h >> w;
	if (2 * h <= l) {
		cout<<"butter";
	} else {
		t = sqrt((2.0 * h - l) / G / 100.0) * w / 60.0 - 0.25;
		if (t - floor(t) > 0.5) {
			cout<<"butter";
		} else {
			cout<<"bread";
		}
	}
}
