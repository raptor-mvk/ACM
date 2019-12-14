#include <iostream>

using namespace std;

const int BARS_COUNT=3;

int main() {
	int n,*d,cur_pos=0,cur_int,cur_len;
	bool error=false;
	cin>>n;
	d=new int[n];
	for(int i=0;i<n;i++) {
		cin>>d[i];
		d[i]--;
	}
	cur_len=1<<(n-1);
	for(int i=0;i<n;i++)
		if(i%2) {
			cur_int=(BARS_COUNT-((cur_pos/cur_len)>>1)%BARS_COUNT)%BARS_COUNT;
			if(d[n-i-1]==cur_int)
				cur_len>>=1;
			else
				if (d[n-i-1]==(cur_int + 2)%3) {
					cur_pos+=cur_len;
					cur_len>>=1;
				}
				else {
					cout<<-1;
					error=true;
					break;
				}
		}
		else {
			cur_int=((cur_pos/cur_len)>>1)%BARS_COUNT;
			if(d[n-i-1]==cur_int)
				cur_len>>=1;
			else
				if(d[n-i-1]==(cur_int+1)%3) {
					cur_pos+=cur_len;
					cur_len>>=1;
				}
				else {
					cout<<-1;
					error=true;
					break;
				}
		}
		if(!error)
			cout<<cur_pos;
}
