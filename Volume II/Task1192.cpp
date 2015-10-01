// Topic: physics
// Subtopic: movement in gravitational field
// Idea: time of one leap is 2 * Vy / G

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double GRAD_IN_RAD = 57.2957795131;
const double G = 10.0;
const double EPS = 1e-5;

int main() {
	double v, a, k, vx, vy, dist = 0.0;
	cin >> v >> a >> k;
	vx = v * cos(a / GRAD_IN_RAD);
	vy = v * sin(a / GRAD_IN_RAD);
	while (vx > EPS)	{
		dist += vx * 2.0 * vy / G;
		vx /= sqrt(k);
		vy /= sqrt(k);
	}
	cout << setprecision(2) << fixed << dist;
}
