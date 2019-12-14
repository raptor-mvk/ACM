#include <iostream>

using namespace std;

const int MAX_STRING_LENGTH=31;

int main() {
	int n,*lens;
	char *names,*used;
	bool equal;
	cin>>n;
	cin.ignore(1,'\n');
	names=new char[MAX_STRING_LENGTH*n];
	lens=new int[n];
	used=new char[n];
	memset(used,0,n);
	for(int i=0;i<n;i++) {
		cin.getline(names+MAX_STRING_LENGTH*i,MAX_STRING_LENGTH);
		if(cin.eof())
			lens[i]=cin.gcount();
		else
			lens[i]=cin.gcount()-1;
		for(int j=0;j<i;j++)
			if((used[j]<2)&&(lens[i]==lens[j])) {
				equal=true;
				for(int k=0;k<lens[i];k++)
					if(names[MAX_STRING_LENGTH*i+k]!=names[MAX_STRING_LENGTH*j+k]) {
						equal=false;
						break;
					}
				if(equal)	{
					if(!used[j]) {					
						cout.write(names+MAX_STRING_LENGTH*j,lens[j]);
						cout<<'\n';
					}
					used[j]=1;
					used[i]=2;
				}
			}
	}
}
