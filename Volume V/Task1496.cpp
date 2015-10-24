// Topic: strings
// Subtopic: elementary

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_STRING_LENGTH=31;

int main() {
	int n;
	string cur;
	vector<string> names;
	vector<bool> used;
	bool found;
	cin >> n;
	cin.ignore(1, '\n');
	for (int i = 0; i < n; i++) {
    getline(cin, cur, '\n');
    found = false;
		for (int j = 0, count = names.size(); j < count; j++) {
		  if (cur == names[j]) {
        found = true;
        if (!used[j]) {
          used[j] = true;
          cout << cur << '\n';
        }
        break;
		  }
		}
		if (!found) {
      names.push_back(cur);
      used.push_back(false);
		}
	}
}
