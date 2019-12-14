// Topic: peculiar
// Subtopic: code analysis
// Idea: binary search for each element of first list

#include <iostream>

using namespace std;

const int MAGIC_NUMBER = 10000;

int searchPair(int *list, int first, int last, int number) {
	int i = (first + last) / 2;
	if (first < last) {
		if (list[i] + number == MAGIC_NUMBER) {
			return i;
		}
		if (list[i] + number < MAGIC_NUMBER) {
			return searchPair(list, first, --i, number);
		} else {
			return searchPair(list, ++i, last, number);
		}
	}
	return list[first] + number != MAGIC_NUMBER ? -1 : first;
}

int main() {
	int n1, n2, result;
	int *list1, *list2;
	cin >> n1;
	list1 = new int[n1];
	for (int i = 0; i < n1; i++) {
		cin >> list1[i];
	}
	cin >> n2;
	list2 = new int[n2];
	for (int i = 0; i < n2; i++) {
		cin >> list2[i];
	}
	for (int i = 0; i < n1; i++) {
		result = searchPair(list2, 0, n2 - 1, list1[i]);
		if (result != -1) {
			cout << "YES";
			break;
		}
	}
	if (result == -1)
		cout << "NO";
}
