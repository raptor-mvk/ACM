// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

const int MINUTES_IN_HOUR = 60;
const int MINUTES_IN_DAY = 1440;
const int ROUND_ERROR = 30;
const int IGNORE_MINUTES = 0;
const int IGNORE_SECONDS = 6;

int main() {
	int n1, n2, n3, c1, c2, t, k, sum = 0, cur_min, cur_sec;
	cin >> n1 >> c1 >> n2 >> t >> c2 >> n3 >> k;
	for (int i = 0; i < k; i++) {
		cin >> cur_min;
		cin.ignore(1);
		cin >> cur_sec;
		if (cur_min <= IGNORE_MINUTES && cur_sec <= IGNORE_SECONDS) {
			continue;
		}
		if (cur_sec) {
			cur_min++;
		}
		sum += cur_min;
	}
	cout << "Basic:     " << (n1 + c1 * sum) << '\n';
	cout << "Combined:  " << (n2 + (sum > t ? sum - t : 0) * c2) << '\n';
	cout << "Unlimited: " << n3 << '\n';
}
