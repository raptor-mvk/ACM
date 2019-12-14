#include <iostream>

using namespace std;

const int MAX_LENGTH=17;

int main() {
	int emperor=0,macaroni=0,little=0,n;
	char word[MAX_LENGTH];
	cin>>n;
	cin.ignore(1,'\n');
	for(int i=0;i<n;i++) {
		cin.getline(word,MAX_LENGTH,'\n');
		switch(word[0])	{
		case 'E':
			emperor++;
			break;
		case 'L':
			little++;
			break;
		case 'M':
			macaroni++;
			break;
		}
	}
	if(macaroni>emperor) {
		if(macaroni>little)
			cout<<"Macaroni Penguin";
		else
			cout<<"Little Penguin";
	}
	else {
		if(emperor>little)
			cout<<"Emperor Penguin";
		else
			cout<<"Little Penguin";
	}
}
