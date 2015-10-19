// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

using namespace std;

const int SMS_LENGTH = 1001;

int main() {
	int sum = 0;
	char sms[SMS_LENGTH];
	cin.getline(sms, SMS_LENGTH);
	for(int i = 0; i < cin.gcount(); i++)
		switch (sms[i]) {
		case 'a': case 'd': case 'g': case 'j': case 'm': case 'p': case 's':
		case 'v': case 'y':	case '.': case ' ':
			sum++;
			break;
		case 'b': case 'e': case 'h': case 'k': case 'n': case 'q': case 't':
		case 'w': case 'z':	case ',':
			sum += 2;
			break;
		case 'c': case 'f': case 'i': case 'l': case 'o': case 'r': case 'u':
		case 'x': case '!':
			sum += 3;
			break;
		}
	cout << sum;
}
