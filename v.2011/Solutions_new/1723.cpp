#include <iostream>

using namespace std;

const int LETTERS_COUNT=26;

int main() {
  char c,imax=0;
  int letters[LETTERS_COUNT];
  memset(letters,0,LETTERS_COUNT*sizeof(int));
  cin.get(c);
  while(!cin.eof()) {
    if((c>='a')&&(c<='z')) {
      c-='a';
      letters[(int)c]++;
      if(letters[(int)c]>letters[(int)imax])
        imax=c;
    }
    cin.get(c);
  }
  cout<<(char)(imax+'a');
}
