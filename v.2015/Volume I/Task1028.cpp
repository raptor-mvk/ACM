// Topic: data structures
// Subtopic: binary tree

#include <iostream>
#include <cstring>

using namespace std;

const int TREE_SIZE = 65536;
const int STEPS_COUNT = 15;
const int INITIAL_MASK = 16384;
const int MAX_N = 15000;

int find_level(int x, int *starsToLeft) {
	int cur_level = 0, cur_step = INITIAL_MASK, cur_position = 1;
	for (int i = 0; i < STEPS_COUNT; i++) {
		if ((x & cur_step) > 0) {
			cur_level += starsToLeft[cur_position - 1];
			cur_position <<= 1;
			cur_position++;
			x -= cur_step;
		}	else {
			starsToLeft[cur_position - 1]++;
			cur_position <<= 1;
		}
		cur_step >>= 1;
	}
	cur_level += starsToLeft[cur_position - 1];
	starsToLeft[cur_position - 1]++;
	return cur_level;
}

int main() {
	int n, x, y, starsToLeft[TREE_SIZE], levelStars[MAX_N];
	memset(starsToLeft, 0, TREE_SIZE * sizeof(int));
	memset(levelStars, 0, MAX_N * sizeof(int));
	cin >> n;
	for (int i = 0; i < n; i++)	{
    cin >> x >> y;
		levelStars[find_level(x, starsToLeft)]++;
	}
	for (int i = 0; i < n; i++) {
    cout << levelStars[i] << '\n';
	}
}
