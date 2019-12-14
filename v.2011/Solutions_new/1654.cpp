#include <iostream>

using namespace std;

const int MAX_SIZE=200001;

int main() {
	char str[MAX_SIZE],result[MAX_SIZE];
	int len,last=0;
	cin.getline(str,MAX_SIZE);
	if(cin.eof())
		len=cin.gcount();
	else
		len=cin.gcount()-1;
	for(int i=0;i<len;i++) {
		result[last++]=str[i];
		while((last>1)&&(result[last-1]==result[last-2]))
			last-=2;
	}
	if(last>0)
		cout.write(result,last);
}
