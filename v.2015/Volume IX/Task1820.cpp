// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    if (k > n) {
    	cout<<2;
    }
    else {
      cout << (n * 2 / k + ((n * 2) % k > 0));
    }
}
