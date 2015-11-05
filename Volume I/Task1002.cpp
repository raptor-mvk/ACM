// Topic: graph
// Subtopic: Lee algorithm
// Idea: vertices of graph are digits in phone number, edges are words of
//       dictionary

#include "../Tools/Reader.h"
#include "../Tools/Graph.h"

const int MAX_WORD_LENGTH = 152;
const int MAX_DATA_SIZE = 300 * 1024 + 1;

char processFunc(char symbol) {
	switch (symbol)
	{
	case 'i': case 'j':
		return '1';
	case 'a': case 'b': case 'c':
		return '2';
	case 'd': case 'e': case 'f':
		return '3';
	case 'g': case 'h':
		return '4';
	case 'k': case 'l':
		return '5';
	case 'm': case 'n':
		return '6';
	case 'p': case 'r': case 's':
		return '7';
	case 't': case 'u': case 'v':
		return '8';
	case 'w': case 'x': case 'y':
		return '9';
	case 'o': case 'q': case 'z':
		return '0';
	}
	return 0;
}

int main() {
  FString::setMaxLength(MAX_WORD_LENGTH);
	int n;
	char *data = new char[MAX_DATA_SIZE];
	FString phone, *dictionary, *words;
	Reader *r;
	Graph *g;
	vector<int> pos;
	r = new Reader(cin, data, MAX_DATA_SIZE);
	r->fill();
	while(true) {
		r->getNext(&phone, &isDelim, 'f', true);
		if (phone[0] == '-')
			break;
		g = new Graph(phone.getLength() + 1, true);
		r->getNext<int>(&n, 'f', true);
		dictionary = new FString[n];
		words = new FString[n];
		for (int i = 0; i < n; i++) {
			r->getNext(words + i, &isDelim, 'f', true);
			dictionary[i] = words[i].process(&processFunc);
			pos.clear();
			phone.find(dictionary[i], &pos);
			for (int j = 0, count = pos.size(); j < count; j++)
				g->addEdge(pos[j], pos[j] + dictionary[i].length, i + 1);
		}
		pos.clear();
		g->findWayLee(0, phone.getLength(), &pos);
		if (pos.size()) {
			for (int i = pos.size() - 1; i > 0; i--) {
				cout << words[(*g)[pos[i]][pos[i - 1]] - 1];
				if (i > 1) {
					cout << ' ';
				}	else {
					cout << '\n';
				}
			}
		} else {
			cout << "No solution.\n";
		}
		delete [] dictionary;
		delete [] words;
		delete g;
	}
}
