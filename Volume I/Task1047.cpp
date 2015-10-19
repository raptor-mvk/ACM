// Topic: arithmetic
// Subtopic: elementary
// Idea: 2 * a(i)= a(i - 1) + a (i + 1) - 2 * c (i) =>
//       a(i) - a(i - 1) = a(i + 1) - a(i) - 2 * c(i) =>
//       d(i) = d(i + 1) - 2 * c (i) =>
//       d(n + 1) = d(1) + 2 * sum(c(i); i = 1 .. n);
//       a(n + 1) - a(0) = d(1) + 2 * sum(d(i); i = 2 .. n + 1) =>
//       a(n + 1) - a(0) = d(1) + sum(d1 + 2 * sum(c(i); j = 1 .. i -1);
//                                    i = 2 .. n + 1) =>
//       a(n + 1) - a(0) = (n + 1) * d(1) + 2 * sum((n - i + 1) * c(i);
//                                                   i = 2 .. n + 1) =>
//       a(1) = a(0) + (a(n + 1) - a(0) -
//                2 * sum((n - i + 1) * c(i); i = 2 .. n + 1)) / (n + 1)

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int n;
	double *c, *csums, *a, a0, an;
	cin >> n >> a0 >> an;
	c = new double[n];
	csums = new double[n];
	a = new double[n];
	for (int i = 0; i < n; i++)
		cin >> c[i];
	if (n == 1) {
		cout << setprecision(2) << fixed << ((a0 + an) / 2.0 - c[0]);
	} else {
		csums[0] = a0 / 2.0;
		for (int i = 1; i < n; i++) {
			csums[i] = (csums[i - 1] - c[i - 1]) * i / (i + 1.0);
		}
		a[n - 1] = (csums[n - 1] - c[n - 1] + an / 2.0) /
		             (1.0 - (n - 1.0) / 2.0 / n);
		for (int i = n - 2; i > 0; i--) {
			a[i] = (csums[i] - c[i] + a[i + 1] / 2.0) / (1.0 - i / 2.0 / (i + 1.0));
		}
		cout << setprecision(2) << fixed << (csums[0] - c[0] + a[1] / 2.0);
	}
}
