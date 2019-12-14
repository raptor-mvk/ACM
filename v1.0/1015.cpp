#include <iostream>

using namespace std;

const int MAX_Q=30;
const int MAX_N=10000;
const int DICE_SIDES=6;

void rotate_left(int *dice) {
	int t;
	t=dice[0];
	dice[0]=dice[2];
	dice[2]=dice[1];
	dice[1]=dice[4];
	dice[4]=t;
}

void rotate_right(int *dice) {
	int t;
	t=dice[0];
	dice[0]=dice[4];
	dice[4]=dice[1];
	dice[1]=dice[2];
	dice[2]=t;
}

void rotate_back(int *dice) {
	int t;
	t=dice[0];
	dice[0]=dice[5];
	dice[5]=dice[1];
	dice[1]=dice[3];
	dice[3]=t;
}

void rotate_front(int *dice) {
	int t;
	t=dice[0];
	dice[0]=dice[3];
	dice[3]=dice[1];
	dice[1]=dice[5];
	dice[5]=t;
}

void rotate_up(int *dice) {
	int t;
	t=dice[2];
	dice[2]=dice[3];
	dice[3]=dice[4];
	dice[4]=dice[5];
	dice[5]=t;
}

void rotate_down(int *dice) {
	int t;
	t=dice[2];
	dice[5]=dice[5];
	dice[5]=dice[4];
	dice[4]=dice[3];
	dice[3]=t;
}

int get_index(int *dice, bool opposite) {
	if(opposite)
		return 24+(6-dice[3])*2+(dice[4]>dice[5]?0:1);
	return (6-dice[1])*6+(((dice[3]-dice[5])*(dice[3]-dice[4])<0)?2:
		((dice[3]-dice[5]>0)?0:4))+(dice[4]>dice[5]?0:1);
}

void unify_dice(int *dice, int one_pos, int two_pos, bool *opposite) {
	int temp;
	temp=one_pos*two_pos;
	if((temp==2)||(temp==15)||(temp==24)) {
		*opposite=true;
		switch(one_pos) {
			case 2:
				rotate_back(dice);
				rotate_back(dice);
				break;
			case 3:
				rotate_left(dice);
				break;
			case 4:
				rotate_front(dice);
				break;
			case 5:
				rotate_right(dice);
				break;
			case 6:
				rotate_back(dice);
				break;
		}
		if(dice[5]==3)
			rotate_down(dice);
		else
			while(dice[2]!=3)
				rotate_up(dice);
	}
	else
	{
		*opposite=false;
		if(one_pos==2) {
			switch(two_pos) {
				case 3:
					rotate_front(dice);
					rotate_front(dice);
					break;
				case 4:
					rotate_front(dice);
					rotate_front(dice);
					rotate_down(dice);
					break;
				case 5:
					rotate_left(dice);
					rotate_left(dice);
					break;
				case 6:
					rotate_front(dice);
					rotate_front(dice);
					rotate_up(dice);
					break;
			}
		}
		else {
			switch(one_pos) {
				case 3:
					rotate_left(dice);
					break;
				case 4:
					rotate_front(dice);
					break;
				case 5:
					rotate_right(dice);
					break;
				case 6:
					rotate_back(dice);
					break;
			}
			if(dice[5]==2)
				rotate_down(dice);
			else
				while(dice[2]!=2)
					rotate_up(dice);
		}
	}
}

int main() {
	int n,one_pos,two_pos,cur_index,schemes_count=0;
	bool opposite;
	int *dices;
	int cur_dice[DICE_SIDES];
	int dices_count[MAX_Q];
	char output_order[MAX_Q];
	dices=new int[MAX_Q*MAX_N];
	cin>>n;
	memset(dices,0,MAX_N*MAX_Q*sizeof(int));
	memset(output_order,0,MAX_Q);
	memset(dices_count,0,MAX_Q*sizeof(int));
	for(int i=0;i<n;i++) {
		for(int j=0;j<DICE_SIDES;j++) {
			cin>>cur_dice[j];
			if(cur_dice[j]==1)
				one_pos=j+1;
			if(cur_dice[j]==2)
				two_pos=j+1;
		}
		unify_dice(cur_dice,one_pos,two_pos,&opposite);
		cur_index=get_index(cur_dice,opposite);
		dices[cur_index*MAX_N+dices_count[cur_index]]=i+1;
		if(dices_count[cur_index]==0)
			output_order[schemes_count++]=cur_index;
		dices_count[cur_index]++;
	}
	cout<<schemes_count<<'\n';
	for(int i=0;i<schemes_count;i++) {
		cout<<dices[output_order[i]*MAX_N];
		for(int j=1;dices[output_order[i]*MAX_N+j]!=0;j++)
			cout<<' '<<dices[output_order[i]*MAX_N+j];
		cout<<'\n';
	}
}
