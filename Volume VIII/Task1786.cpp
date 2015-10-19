// Topic: arithmetic
// Subtopic: elementary

#include <iostream>

const int MAX_STRING_LENGTH = 201;

using namespace std;

int main() {
	char str[MAX_STRING_LENGTH];
	char name[6] = {'S', 'a', 'n', 'd', 'r', 'o'};
	int len, sum = 60, cur;
	cin.getline(str, MAX_STRING_LENGTH);
	if (cin.eof()) {
		len = cin.gcount();
	} else {
		len = cin.gcount() - 1;
	}
	for (int i = 0; i < len - 5; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			if (str[i] == 'S') {
				cur = 0;
			}	else {
				cur = 5;
			}
		}	else {
			if (str[i] == 's') {
				cur = 5;
			}	else {
				cur = 10;
			}
		}
		if (cur < sum) {
			for (int j = 1; j < 6 && cur < sum; j++)
				if (str[i + j] >= 'A' && str[i + j] <= 'Z') {
					if ((char)tolower(str[i + j]) == name[j]) {
						cur += 5;
					}	else {
						cur += 10;
					}
				}	else if (str[i + j] != name[j]) {
						cur += 5;
				}
		}
		if (cur < sum) {
			sum = cur;
		}
	}
	cout << sum;
}
