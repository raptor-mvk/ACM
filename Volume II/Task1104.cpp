// Topic: arithmetic
// Subtopic: elementary
// Idea: full search

#include "../Tools/Reader.h"

const int MAX_N = 36;
const int MAX_DATA_SIZE = 1000001;

int main() {
  int sum = 0, start = 1;
  char *data;
  bool found = false;
  Reader *r;
  data = new char[MAX_DATA_SIZE];
  r = new Reader(cin, data, MAX_DATA_SIZE);
  r->fill();
  for (int i = 0; i < r->getLength(); i++) {
  	if ((data[i] >= '0' && data[i] <= '9') ||
     (data[i] >= 'A' && data[i] <= 'Z')) {
	    sum += data[i] > '9' ? data[i] - 'A' + 10 : data[i] - '0';
  	  start = data[i] > '9' ? (data[i] - 'A' + 10 > start ?
        data[i] - 'A' + 10 : start) :	(data[i] - '0' > start ?
        data[i] - '0' : start);
		}
  }
  for (int i = start; i < MAX_N; i++) {
    if (!(sum % i)) {
			cout << (i + 1);
			found = true;
      break;
    }
  }
  if (!found) {
  	cout<<"No solution.";
  }
}
