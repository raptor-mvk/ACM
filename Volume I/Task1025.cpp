// Topic: arithmetic
// Subtopic: elementary

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int k, count = 0;
	cin >> k;
	vector<int> data(k);
	for (int i = 0; i < k; i++) {
		cin >> data[i];
	}
	sort(data.begin(), data.end());
	for (int i = 0; i < k / 2 + k % 2; i++)
		count += data[i] / 2 + data[i] % 2;
	cout << count;
}
