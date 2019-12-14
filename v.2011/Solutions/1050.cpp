#include <stdio.h>

const int MAX_LENGTH=30000;

int main()
{
  char c,new_par=0,cur_quote=0,par_pos=0,no_print=0;
  int buf_pos=0;
  char *buffer=new char[MAX_LENGTH];
  while((c=getchar())!=EOF)
  {
    if((new_par==1)&&(c!='\r')&&(c!='\n'))
      new_par=0;
    if(c=='\n')
      new_par++;
    else if(c=='\\') par_pos=1;
    else if(c=='"')
    {
      if(par_pos!=1) no_print=1;
      if((par_pos!=1)&&(cur_quote==1))
      {
        printf("``");
        for(int i=0;i<buf_pos;i++)
          printf("%c",buffer[i]);
        buf_pos=0;
        printf("''");
        cur_quote=0;
      }
      else if((par_pos!=1)&&(cur_quote==0))
        cur_quote=1;
    }
    else
    {
      if(par_pos==1)
      {
        if(c=='p') par_pos++;
        else par_pos=0;
      }
      else if(par_pos==2)
      {
        if(c=='a') par_pos++;
        else par_pos=0;
      }
      else if(par_pos==3)
      {
        if(c=='r') new_par=2;
        else par_pos=0;
      }
    }
    if(new_par==2)
    {
      for(int i=0;i<buf_pos;i++)
        printf("%c",buffer[i]);
      new_par=0;
      buf_pos=0;
      cur_quote=0;
    }
    if(!no_print)
    {
      if(cur_quote==0) printf("%c",c);
      else buffer[buf_pos++]=c;
    }
    else no_print=0;
  }
  for(int i=0;i<buf_pos;i++)
    printf("%c",buffer[i]);
}
