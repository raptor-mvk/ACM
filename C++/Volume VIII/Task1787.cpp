// Topic: elementary

#include <iostream>

using namespace std;

int main()
{
  int n, k, cur, jam = 0;
  cin >> k >> n;
  while (n-- > 0) {
    cin >> cur;
    jam += cur - k;
    if (jam < 0) {
      jam = 0;
    }
  }
  cout << jam;
}
