#include <iostream>

using namespace std;

const int MINUTES_IN_HOUR=60;
const int MINUTES_IN_DAY=1440;
const int ROUND_ERROR=30;

int main() {
	int hours_begin_there,hours_end_there,hours_begin_here,hours_end_here;
	int minutes_begin_there,minutes_end_there,minutes_begin_here,minutes_end_here;
	int result;
	cin>>hours_begin_here;
	cin.ignore(1);
	cin>>minutes_begin_here;
	cin>>hours_end_there;
	cin.ignore(1);
	cin>>minutes_end_there;
	cin>>hours_begin_there;
	cin.ignore(1);
	cin>>minutes_begin_there;
	cin>>hours_end_here;
	cin.ignore(1);
	cin>>minutes_end_here;
	result=(abs(((hours_end_there*MINUTES_IN_HOUR+minutes_end_there-
		hours_begin_here*MINUTES_IN_HOUR-minutes_begin_here+MINUTES_IN_DAY)%
		MINUTES_IN_DAY-(hours_end_here*MINUTES_IN_HOUR+minutes_end_here-
		hours_begin_there*MINUTES_IN_HOUR-minutes_begin_there+MINUTES_IN_DAY)%
		MINUTES_IN_DAY)/2)+ROUND_ERROR)/MINUTES_IN_HOUR;
	cout<<((result>5)?5:result);
}
