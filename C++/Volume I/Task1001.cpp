// Topic: elementary

#include <iostream>
#include <iomanip>
#include <stack>
#include <cmath>

using namespace std;

int main()
{
  stack<double> st;
  long long a;
  while(cin >> a) {
    st.push(sqrt((double)a));
  }
  cout << fixed << setprecision(4);
  while(!st.empty()) {
    cout << st.top() << endl;
    st.pop();
  }
}