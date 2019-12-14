#include <stdio.h>
#include <memory.h>
#include <math.h>

const int STACK_SIZE=5;
const int INDEX_SIZE=1000;
const int MAX_ELEMS=100000+STACK_SIZE*INDEX_SIZE;
const int ADDRESS_SIZE=MAX_ELEMS/STACK_SIZE;

int *stack,*prev_address,*index;
char *stack_pos, sym;
int n,i,k,m,cur_address=0;

int main()
{
#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif
	stack = new int[MAX_ELEMS];
	prev_address = new int[ADDRESS_SIZE];
	index = new int[INDEX_SIZE];
	stack_pos = new char[ADDRESS_SIZE];
	memset(index,-1,INDEX_SIZE*sizeof(int));
	memset(prev_address,-1,ADDRESS_SIZE*sizeof(int));
	scanf("%d\n",&n);
	for (i=0;i<n;i++)
	{
		scanf("P%c", &sym);
		if (sym=='U')
		{
			scanf("SH%d%d\n", &k, &m);
			k--;
			if (*(index + k)==-1)
			{
				*(stack + cur_address * STACK_SIZE) = m;
				*(stack_pos + cur_address) = 1;
				*(index + k) = cur_address++;
			}
			else
			{
				if (*(stack_pos + *(index + k)) < STACK_SIZE)
				{
					*(stack + *(index + k) * STACK_SIZE + *(stack_pos + *(index + k))) = m;
					stack_pos[*(index + k)]++;
				}
				else
				{
					*(prev_address + cur_address) = *(index + k);
					*(stack + cur_address * STACK_SIZE) = m;
					*(stack_pos + cur_address) = 1;
					*(index + k) = cur_address++;
				}
			}
		}
		else
		{
			scanf("P%d\n", &k);
			k--;
			if (*(stack_pos + *(index + k)) > 1)
			{
				printf("%d\n", *(stack + *(index + k) * STACK_SIZE + *(stack_pos + *(index + k)) - 1));
				stack_pos[*(index + k)]--;
			}
			else
			{
				printf("%d\n", *(stack + *(index + k) * STACK_SIZE + *(stack_pos + *(index + k)) - 1));
				stack_pos[*(index + k)]--;
				*(index + k) = *(prev_address + *(index + k));
			}
		}
	}
}