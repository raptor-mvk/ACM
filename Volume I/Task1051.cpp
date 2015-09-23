// Topic: games
// Idea: if m = 1 then answer is n / 2 + n % 2
//       if n = 1 then answer is m / 2 + m % 2
//       if m or n is divisible by 3, then answer is 2
//       otherwise answer is 1

#include <iostream>

using namespace std;

int main() {
  int m,n;
  cin>>m>>n;
  cout<<((m==1)?(n/2+(n%2)):((n==1)?(m/2+(m%2)):(1+(!(m%3)||!(n%3)))));
}
