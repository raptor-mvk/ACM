// Topic: math
// Subtopic: trigonometry + derivatives
// Idea: displacement to the left is H / 2 * cos(a) - h / tan(a),
//       where a is angle between book and shelf

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
  int h, H;
  double s, c;
  cin >> h >> H;
  if (h * 2 < H) {
    s = pow(2.0 * h / H, 1.0 / 3.0);
    c = pow(1 - s * s, 0.5);
    cout << fixed << setprecision(6) << (c * H / 2 - h * c / s);
  }
  else
    cout << 0;
}
