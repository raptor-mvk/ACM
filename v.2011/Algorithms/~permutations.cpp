// Генератор перестановки по номеру и номеру по перестановке

const int PERM_LENGTH=6;
const int PERM_COUNT=720;

int get_num(char *perm)
{
  char used[PERM_LENGTH];
  int num=0,count;
  memset(used,0,PERM_LENGTH*sizeof(char));
  for(int i=0;i<PERM_LENGTH-1;i++)
  {
    count=-1;
    for(int j=0;j<=perm[i];j++)
      if(!used[j])
        count++;
    num+=count;
    used[perm[i]]=1;
    num*=PERM_LENGTH-1-i;
  }
  return num;
}

void get_pos(int num,char *pos)
{
  char used[PERM_LENGTH];
  int cur_div=PERM_COUNT/PERM_LENGTH;
  int j,count;
  memset(used,0,PERM_LENGTH*sizeof(char));
  for(int i=0;i<PERM_LENGTH-1;i++)
  {
    count=num/cur_div;
    j=0;
    while(count>-1)
      if(!used[j++])
        count--;
    used[--j]=1;
    pos[i]=j;
    num=num%cur_div;
    cur_div=cur_div/(PERM_LENGTH-1-i);
  }
  j=0;
  while (used[j++]);
  pos[PERM_LENGTH-1]=--j;
}
