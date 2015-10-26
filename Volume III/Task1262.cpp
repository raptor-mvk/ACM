// Topic: arithmetic
// Subtopic: elementary

#include "../Tools/Reader.h"

const int MAX_DATA_SIZE=2004;

int main() {
	int result = 0;
	char *data;
	Reader *r;
	data = new char[MAX_DATA_SIZE];
	r = new Reader(cin, data, MAX_DATA_SIZE);
	r->fill();
	for (int i = 0; data[i] >= '0' && data[i] <= '9'; i++)
		switch (data[i]) {
			case '1':	case '5':
				result++;
				break;
			case '2':	case '4':	case '6':	case '9':
				result += 2;
				break;
			case '3':	case '7':
				result += 3;
				break;
			case '8':
				result += 4;
				break;
			case '0':
				break;
		}
	cout << result;
}
