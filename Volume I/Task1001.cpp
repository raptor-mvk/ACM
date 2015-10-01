// Topic: data structures
// Subtopic: stack
// Using reader for speed up input, backward direction instead of stack

#include <iomanip>
#include <cmath>
#include "../Tools/Reader.h"

const int DATA_SIZE = 256 * 1024 + 1;

int main() {
	char *data;
	Reader *r;
	long long temp;
	data = new char[DATA_SIZE];
	r = new Reader(cin, data, DATA_SIZE);
	r->fill();
	cout << fixed << setprecision(4);
	while (r->getNext<long long>(&temp, 'b', false)) {
		cout << sqrt((double)temp) << '\n';
	}
}
