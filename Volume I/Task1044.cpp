// Topic: arithmetic
// Subtopic: elementary

#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int MAX_SUM = 37;

int main() {
	int n, sums[MAX_SUM], curi, cur_sum, result = 0;
	cin >> n;
	n /= 2;
	memset(sums, 0, MAX_SUM * sizeof(int));
	for (int i = 0; i < pow(10.0, (double)n); i++) {
		curi = i;
		cur_sum = 0;
		while (curi > 0) {
			cur_sum += curi % 10;
			curi /= 10;
		}
		sums[cur_sum]++;
	}
	for (int i = 0; i < MAX_SUM; i++) {
		result += sums[i] * sums[i];
	}
	cout << result;
}
