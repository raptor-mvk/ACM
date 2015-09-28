// Topic: arithmetic
// Subtopic: elementary
// Idea: if l is multiple of k, then the answer is determined,
//       otherwise there could be an extra segment

#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int l, k, h;
	cin >> l >> k >> h;
	cout << setprecision(5) << fixed;
	if (!(l % k)) {
		cout << (double)(l / k * h) << ' ' << (double)(l / k * h);
	} else {
		cout << (double)(l / k * h) << ' ' << (double)(l / k * h + h);
	}
}
