// Topic: geometry
// Subtopic: elementary
// Idea: if 2 * r <= n, then the answer is the area of a circle,
//       if 2 * r > n * sqrt(2), then the answer is the area of square
//       otherwise, the answer is the area of intersection of circle and
//       larger square

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const double PI = 3.1415926;

int main() {
	int n, r;
	double res, side, angle;
	cin >> n >> r;
	if (n >= 2 * r) {
		res = PI * r * r;
	} else if (sqrt(2.0) * n < 2.0 * r) {
    res = n * n;
	}	else {
	  side = sqrt(r * r - 0.25 * n * n);
    angle = atan(2.0 * side / n);
	  res = (PI - 4.0 * angle) * r * r + 2.0 * side * n;
  }
	cout << setprecision(3) << fixed << res;
}
