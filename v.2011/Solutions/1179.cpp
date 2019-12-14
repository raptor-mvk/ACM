#include <stdio.h>
#include <memory.h>

const int MAX_K=35;

int main()
{
    char c,cur_num[MAX_K];
    int count[MAX_K],max=0,max_i;
    memset(count,0,MAX_K*sizeof(int));
    memset(cur_num,0,MAX_K*sizeof(char));
    while(scanf("%c",&c)!=EOF)
    {
        if((c=='0')||(c=='1'))
            for(int i=0;i<MAX_K;i++)
                cur_num[i]=1;
        else if((c>='2')&&(c<='9'))
        {
            for(int i=0;i<c-'1';i++)
                if (cur_num[i])
                {
                    count[i]++;
                    cur_num[i]=0;
                }
            for(int i=c-'1';i<MAX_K;i++)
                cur_num[i]=1;
        }
        else if ((c>='A')&&(c<='Z'))
        {
            for(int i=0;i<c-'A'+9;i++)
                if (cur_num[i])
                {
                    count[i]++;
                    cur_num[i]=0;
                }
            for(int i=c-'A'+9;i<MAX_K;i++)
                cur_num[i]=1;
        }
        else
            for(int i=0;i<MAX_K;i++)
                if(cur_num[i])
                {
                    count[i]++;
                    cur_num[i]=0;
                }   
    }
    for(int i=0;i<MAX_K;i++)
        if(cur_num[i])
            count[i]++;
    for(int i=0;i<MAX_K;i++)
        if(count[i]>max)
        {
            max=count[i];
            max_i=i;
        }
    printf("%d %d",max_i+2,max);
}