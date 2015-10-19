// Topic: arithmetic
// Subtopic: elementary
// Idea: the answer it either sum from 1st to kth elements, or
//       the sum from kth to mth elements, if the sum from 1st to kth and
//       the sum from 1st to mth are equal by modulo n

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_N = 10000;

int main() {
	int n, numbers[MAX_N], sums[MAX_N], cur_sum = 0;
	cin >> n;
	memset(sums, 0, MAX_N * sizeof(int));
	for (int i = 0; i < n; i++) {
		cin >> numbers[i];
		cur_sum += numbers[i];
		cur_sum %= n;
		if (!cur_sum) {
			cout << (i + 1) << '\n';
			for (int j = 0; j <= i; j++) {
				cout << numbers[j] << '\n';
			}
			break;
		}
		if (sums[cur_sum]) {
			cout << (i - sums[cur_sum] + 1) << '\n';
			for (int j = sums[cur_sum]; j <= i; j++) {
				cout << numbers[j] << '\n';
			}
			break;
		}	else {
			sums[cur_sum] = i + 1;
		}
	}
}
