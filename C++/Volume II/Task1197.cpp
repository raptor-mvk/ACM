// Topic: elementary
// Idea: answer is 2 for corner squares, 3 for side squares adjacent
//       to corners, 4 for other side squares and corner squares for
//       6x6 sub-board, 6 for other side squares for 6x6 sub-board,
//       8 for other squares

#include <iostream>

using namespace std;

int main()
{
  int n;
  char c1, c2, to_side1, to_side2, min, max;
  cin >> n;
  cin.ignore(1, '\n');
  for (int i = 0; i < n; i++) {
    cin >> c1 >> c2;
    cin.ignore(1, '\n');
    to_side1 = c1 - 'a' > 'h' - c1 ? 'h' - c1 : c1 - 'a';
    to_side2 = c2 - '1' > '8' - c2 ? '8' - c2 : c2 - '1';
    min = to_side1 > to_side2 ? to_side2 : to_side1;
    max = to_side1 > to_side2 ? to_side1 : to_side2;
    if (min > 1) {
      cout << "8\n";
    } else if (max > 1 && min == 1) {
      cout << "6\n";
    } else if ((max > 1 && min == 0) || (max == 1 && min == 1)) {
      cout << "4\n";
    } else if (max == 1 && min == 0) {
      cout << "3\n";
    } if (max == 0) {
      cout<<"2\n";
    }
  }
}
