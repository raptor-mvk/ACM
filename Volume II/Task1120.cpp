// Topic: arithmetic
// Subtopic: elementary
// Idea: if N = A + (A + 1) + ... (A + P - 1) then
//       N = (A - 1) * P + 1 + 2 + ... + P - 1

#include <iostream>

using namespace std;

int main() {
	int n, sum = 1, a, p;
	bool found = false;
	cin >> n;
	for (int i = 2; sum < n; i++) {
		sum = sum + i;
		if(!((n - sum) % i)) {
			found = true;
			p = i;
			a = (n - sum) / i + 1;
		}
	}
	if (found) {
		cout<<a<<' '<<p;
	} else {
		cout<<n<<" 1";
	}
}
