// Topic: arithmetic
// Subtopic: elementary
// Idea: the centipede either puts on 40 right slippers at first,
//       next throws away all remaining right slippers,
//       next puts on 40 left slippers
//       or puts on 39 right slippers, next puts on 40 left slippers,
//       next throws away all remaining left slippers,
//       next puts on last right slipper

#include <iostream>

using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	cout << (a * 2 + 39 > b * 2 + 40 ? a * 2 + 39 : b * 2 + 40);
}
