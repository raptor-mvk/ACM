// Topic: games
// Subtopic: Directly calculated winning positions
// Idea: parity depends only on signs before odd numbers

#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	cout << ((n - 1) % 4 < 2 ? "grimy" : "black");
}
