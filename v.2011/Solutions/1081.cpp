// последовательность длины i можно получить двумя способами:
// 1. дописать 0 в конец последовательности длины i - 1
// 2. дописать 01 в конец последовательности длины i - 2
// последовательность длины n с номером k формируется по следующему алгоритму:
// 1. пока n > 0
//    a. находим такую длину последовательности n1, что число
//       последовательностей длины n1-1 больше или равно k
//    b. выводим n1 - n нулей
//    c. n = n1
//    d. если k больше 2, то
//       i. уменьшаем k на количество последовательностей длины n1 - 2
//       ii. если n = 1, то печатаем 1, иначе 10
//       iii. уменьшаем n на 2
//    e. если k = 2, то
//       i. печатаем 1
//       ii. n = 0
//    f. если k = 1, то
//       i. n = 0
//       ii. печатаем n1 нулей

#include <iostream>

using namespace std;

int main()
{
  int i,n,k,*numbers_count;
  cin>>n>>k;
  numbers_count=new int[n];
  numbers_count[0]=2;
  numbers_count[1]=3;
  for(int j=2;j<n;j++)
    numbers_count[j]=numbers_count[j-1]+numbers_count[j-2];
  if(k<=numbers_count[n-1])
    while(n>0)
    {
      i=0;
      while(numbers_count[i++]<k);
      for(int j=i;j<n;j++)
        cout<<0;
      n=i;
      if(k>2)
      {
        k-=numbers_count[i-2];
        if(n==1)
          cout<<"1";
        else
          cout<<"10";
        n-=2;       
      }
      else
      {
        n=0;
        if(k==1)
          for(;i>0;i--)
            cout<<"0";
        else
          cout<<"1";
      }
    }
  else
    cout<<"-1";
}