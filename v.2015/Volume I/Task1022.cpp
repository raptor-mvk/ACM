// Topic: graph
// Subtopic: elementary

#include "../Tools/MVector.h"
#include <iostream>

int main() {
	vector<int> queue;
	int n, cur;
	unsigned int start = 0;
	cin >> n;
	vector2<int> children(n,0);
	vector<int> parents(n);
	for (int i = 0; i < n; i++) {
		cin >> cur;
		while (cur--) {
			children[i].push_back(cur);
			parents[cur]++;
			cin >> cur;
		}
	}
	for (int i = 0; i < n; i++) {
		if (!parents[i]) {
			queue.push_back(i);
		}
	}
	while (start < queue.size()) {
		cout << (queue[start] + 1) << ' ';
		for (int i = 0, count = children[queue[start]].size(); i < count;i++) {
			if (!(--parents[children[queue[start]][i]])) {
				queue.push_back(children[queue[start]][i]);
			}
		}
		start++;
	}
}
