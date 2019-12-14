#include <stdio.h>

const int MAX_WORD_LENGTH=9;
const int MAX_WORDS_COUNT=101;
const int MAX_LENGTH=10000;

int word_cmp(char *word1, char *word2, int *mistakes)
{
  int i=0,j=0,errors=0;
  while(1)
  {
    if((word1[i]==0)&&(word2[j]!=0))
      return 0;
    if((word1[i]!=0)&&(word2[j]==0))
      return 0;
    if((word1[i]==0)&&(word2[j]==0))
    {
      *mistakes+=errors;
      return 1;
    }
    if((word1[i]!=word2[j]))
    {
      if(!errors) errors++;
      else return 0;
    }
    i++;
    j++;
  }
}

int main()
{
  char *words=new char[MAX_WORDS_COUNT*MAX_WORD_LENGTH];
  char *buffer=new char[MAX_LENGTH];
  int words_count=0,cur_length=0,mistakes=0;
  char exit=0,c;
  while(!exit)
  {
    scanf("%s\n",&words[MAX_WORD_LENGTH*words_count]);
    if(words[MAX_WORD_LENGTH*words_count]=='#')
      exit=1;
    else words_count++;
  }
  while((c=getchar())!=EOF)
  {
    if((c>='a')&&(c<='z'))
      buffer[cur_length++]=c;
    else
    {
      if(cur_length>0)
      {
        buffer[cur_length]=0;
        exit=0;
        for(int i=0;i<words_count;i++)
          if(word_cmp(&words[MAX_WORD_LENGTH*i],buffer,&mistakes))
          {
            exit=1;
            printf("%s",&words[MAX_WORD_LENGTH*i]);
            break;
          }
        if(!exit) printf("%s",buffer);
        cur_length=0;
      }
      printf("%c",c);
    }
  }
  printf("%d",mistakes);
}