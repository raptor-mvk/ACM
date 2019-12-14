#include <iostream>

using namespace std;

const int TASKS_COUNT=10;
const int PENALTY_COST=20;

int main() {
	int a,b,penalty=0,cur_penalty;
	cin>>a>>b;
	for(i = 0; i < TASKS_COUNT; i++) {
		cin>>cur_penalty;
		penalty+=cur_penalty*PENALTY_COST;
	}
	if(b-penalty<a)
		cout<<"Dirty debug :(";
	else
		cout<<"No chance.";
}
