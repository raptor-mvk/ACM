// Topic: data structures
// Subtopic: tree
// Idea: swap subtrees, all members of left subtree are less
//       than any member of right subtree

#include <iostream>

using namespace std;

const int MAX_N = 3000;

void print(int *tree, int n) {
	int i = 0;
	if (!n) {
		return;
	}
	if (n == 1) {
		cout << tree[0] << ' ';
		return;
	}
	while (tree[i] < tree[n-1]) {
		i++;
	}
	print(tree + i, n - i - 1);
	print(tree, i);
	cout << tree[n - 1] << ' ';
}

int main() {
	int n, *data;
	cin >> n;
	data = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> data[i];
	}
	print(data, n);
}
