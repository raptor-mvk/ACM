// Topic: geometry
// Subtopic: solids of revolution
// Idea: volume of the piece of pineapple is calculated by formula
//       pi * int(y ^ 2 dx), where y = sqrt(b * b - x * x) * a / b

#include <iostream>

using namespace std;

int main() {
	int h, w, n, cur_w, cur_h, len;
	char *word;
	cin >> h >> w >> n;
	cin.ignore(1, '\n');
	word = new char[w + 1];
	cur_w = w;
	cur_h = 0;
	for (int i = 0; i < n; i++) {
		cin.getline(word, w + 1);
		len = cin.gcount() - 1;
		if (cur_w + 1 + len <= w) {
			cur_w += len + 1;
		} else {
			cur_h++;
			cur_w = len;
		}
	}
	cout << cur_h / h + (cur_h % h ? 1 : 0);
}
