// Topic: arithmetic
// Subtopic: elementary

#include "../Tools/Reader.h"

const int MAX_DATA_SIZE=30001;
const int N=1999;

int jury(int n, int q) {
  if (n == 1) {
		return 0;
  } else {
		return (jury (n - 1, q) + q) % n;
  }
}

int main() {
  FString::setMaxLength(MAX_DATA_SIZE);
  int last;
  char *data;
  FString question, str;
  Reader *r;
  data = new char[MAX_DATA_SIZE];
  r = new Reader(cin, data, MAX_DATA_SIZE);
  r->fill();
  while(r->getNext(&str, &isEndl, 'f', true))
  	question += str;
  last = jury(question.getLength(), N);
  if (question[last] == '?') {
		cout << "Yes";
  } else if (question[last] == ' ') {
		cout<<"No";
  } else {
		cout<<"No comments";
  }
}
