// ������������������ ����� i ����� �������� ����� ���������:
// 1. �������� 0 � ����� ������������������ ����� i - 1
// 2. �������� 01 � ����� ������������������ ����� i - 2
// ������������������ ����� n � ������� k ����������� �� ���������� ���������:
// 1. ���� n > 0
//    a. ������� ����� ����� ������������������ n1, ��� �����
//       ������������������� ����� n1-1 ������ ��� ����� k
//    b. ������� n1 - n �����
//    c. n = n1
//    d. ���� k ������ 2, ��
//       i. ��������� k �� ���������� ������������������� ����� n1 - 2
//       ii. ���� n = 1, �� �������� 1, ����� 10
//       iii. ��������� n �� 2
//    e. ���� k = 2, ��
//       i. �������� 1
//       ii. n = 0
//    f. ���� k = 1, ��
//       i. n = 0
//       ii. �������� n1 �����

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