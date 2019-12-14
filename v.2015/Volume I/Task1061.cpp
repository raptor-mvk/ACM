// Topic: arithmetic
// Subtopic: elementary
// Idea: full search

#include "../Tools/Reader.h"

const int MAX_DATA_SIZE = 102000;

int main() {
  FString::setMaxLength(MAX_DATA_SIZE);
  int n, k, min = 10 * MAX_DATA_SIZE, start = -1, cur = 0, count = 0;
  char *data;
  FString str, temp;
  Reader *r;
	data = new char[MAX_DATA_SIZE];
	r = new Reader(cin, data, MAX_DATA_SIZE);
	r->fill();
	r->getNext<int>(&n, 'f', false);
	r->getNext<int>(&k, 'f', true);
	while(r->getNext(&temp, &isEndl, 'f', true)) {
		str += temp;
	}
	for (int i = 0; i < str.getLength(); i++) {
		if (str[i] >= '0' && str[i] <= '9') {
      cur += str[i] - '0';
      count++;
      if (count > k) {
        cur -= str[i - k] - '0';
        count--;
        if (cur < min) {
          min = cur;
          start = i - k + 1;
        }
      } else if (count == k) {
        if (cur < min) {
          min = cur;
          start = i - k + 1;
        }
      }
		} else {
      cur = 0;
      count = 0;
    }
	}
	cout << (start + 1);
}
