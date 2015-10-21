// Topic: arithmetic
// Subtopic: elementary
// Idea: answer is a half of difference between flight lengths

#include <iostream>
#include <cmath>

using namespace std;

const int MINUTES_IN_HOUR = 60;
const int MINUTES_IN_DAY = 1440;
const int ROUND_ERROR = 30;

int main() {
	int hBegThere, hEndThere, hBegHere, hEndHere;
	int mBegThere, mEndThere, mBegHere, mEndHere;
	int result;
	cin >> hBegHere;
	cin.ignore(1);
	cin >> mBegHere;
	cin >> hEndThere;
	cin.ignore(1);
	cin >> mEndThere;
	cin >> hBegThere;
	cin.ignore(1);
	cin >> mBegThere;
	cin >> hEndHere;
	cin.ignore(1);
	cin >> mEndHere;
	result = (abs(((hEndThere * MINUTES_IN_HOUR + mBegThere -
		hBegHere * MINUTES_IN_HOUR - mBegHere + MINUTES_IN_DAY) %
		MINUTES_IN_DAY - (hEndHere * MINUTES_IN_HOUR + mEndHere -
		hBegThere * MINUTES_IN_HOUR - mBegThere + MINUTES_IN_DAY) %
		MINUTES_IN_DAY) / 2) + ROUND_ERROR) / MINUTES_IN_HOUR;
	cout << (result > 5 ? 5 : result);
}
